#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "ryml.hpp"
#include "ryml_std.hpp"

class Settings {
public:
    Settings(const std::string& filename) : filename_(filename) {
        std::ifstream file(filename_);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename_ << std::endl;
            return;
        }
        std::string yaml_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        // 复制内容到一个可以修改的缓冲区
        buffer_ = yaml_content; 
        ryml::substr yaml_substr = ryml::to_substr(buffer_);
        try {
            tree_ = ryml::parse_in_place(yaml_substr);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing YAML: " << e.what() << std::endl;
        }
    }

    void setValue(const std::string& path, const std::string& value) {

        std::cout << std::endl << std::endl;
        std::cout << "Setting value: " << value << " for path: " << path << std::endl;

        // Make a copy of value to ensure it remains valid
        std::string value_copy = value;

        // Convert to csubstr and print debug info
        ryml::csubstr cstr_value = ryml::to_csubstr(value_copy);
        std::cout << "Converted csubstr value: " << std::string(cstr_value.str, cstr_value.len) << std::endl;

        auto node = getNode(path);
        node.set_val_serialized(cstr_value);
        if (node.is_seed() || node.is_val()) {
            node.set_val(cstr_value);
            std::cout << "Node after setting value: " << node.val().str << std::endl;
        }
        else {
            // std::cerr << "Invalid path: " << path << std::endl;
        }

        // std::cerr << "return: " << std::endl;
        return;

    }


    /*
    void setValue(const std::string& path, const std::string& value) {
        std::cout << "Setting value: " << value << " for path: " << path << std::endl;

        // Convert to csubstr and print debug info
        ryml::csubstr cstr_value = ryml::to_csubstr(value);
        std::cout << "Converted csubstr value: " << std::string(cstr_value.str, cstr_value.len) << std::endl;

        auto node = getNode(path);
        node.set_val(cstr_value);
        if (node.is_seed() || node.is_val()) {
            node.set_val(cstr_value);
        }
        else {
            std::cerr << "Invalid path: " << path << std::endl;
        }

        std::cerr << "return: " << std::endl;
        return;
    }
    */

    std::string value(const std::string& path) {
        auto node = getNode(path);
        if (node.valid() && node.has_val()) {
            std::string node_value = node.val().str;
            size_t pos = node_value.find_first_of("\n ");
            if (pos != std::string::npos) {
                node_value = node_value.substr(0, pos);
            }
            return node_value;
        }
        else {
            std::cerr << "Invalid path or node has no value: " << path << std::endl;
            return "";
        }
    }


    void save() {
        std::cout << std::endl << std::endl;
        std::cout << "Saving settings..." << std::endl;

        // Print tree content before saving
        // std::string buffer;
        // ryml::emit_yaml(tree_, ryml::to_substr(buffer));
        // std::cout << "Tree content before saving:\n" << buffer << std::endl;

        FILE* file = std::fopen(filename_.c_str(), "w");
        if (!file) {
            std::cerr << "Failed to open file for saving: " << filename_ << std::endl;
            return;
        }

        size_t len = ryml::emit_yaml(tree_, tree_.root_id(), file);
        // size_t len = fwrite(buffer.data(), 1, buffer.size(), file);
        std::fclose(file);

        std::cout << "Settings saved to " << filename_ << " (" << len << " characters written)" << std::endl;
    }

private:
    c4::yml::NodeRef getNode(const std::string& path) {
        std::istringstream iss(path);
        std::string token;
        auto node = tree_.rootref();
        while (std::getline(iss, token, '/')) {
            if (!token.empty()) {
                if (!node.has_child(token.c_str())) {
                    node |= ryml::MAP;
                    node[token.c_str()] = ryml::NodeRef{};
                }
                node = node[token.c_str()];
                if (!node.valid()) {
                    std::cerr << "Invalid path segment: " << token << std::endl;
                    break;
                }
                else {
                    // std::cerr << "Valid path segment: " << token << std::endl;
                    continue;
                }
            }
        }
        return node;
    }


    std::string filename_;
    std::string buffer_;
    ryml::Tree tree_;
};

int main() {
    const std::string filename = "config.yaml";

    // 创建或打开文件，并写入一些初始配置
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Failed to create or open file: " << filename << std::endl;
        return 1;
    }
    outfile << "editor:\n"
            << "  wrapMargin: 80\n"
            << "  tabSize: 4\n"
            << "user:\n"
            << "  name: John Doe\n"
            << "  email: johndoe@example.com\n";
    outfile.close();

    // 读取并打印配置
    Settings settings(filename);
    std::string wrapMargin = settings.value("editor/wrapMargin");
    std::string tabSize = settings.value("editor/tabSize");
    std::string userName = settings.value("user/name");
    std::string userEmail = settings.value("user/email");

    std::cout << "Initial configuration:\n\n";
    std::cout << "editor/wrapMargin: " << wrapMargin << std::endl;
    std::cout << "editor/tabSize: " << tabSize << std::endl;
    std::cout << "user/name: " << userName << std::endl;
    std::cout << "user/email: " << userEmail << std::endl;

    // 修改其中一个值并保存
    settings.setValue("editor/wrapMargin", "100");
    settings.setValue("editor/tabSize", "200");
    settings.setValue("user/name", "Fokatu");
    settings.setValue("user/email", "Fokatu@Fokatu.com");
    settings.save();

    // 重新读取并打印配置
    // std::cout << "\nUpdated configuration:\n";
    // wrapMargin = settings.value("editor/wrapMargin");
    // std::cout << "editor/wrapMargin: " << wrapMargin << std::endl;

    // 读取并打印配置
    Settings settings1(filename);
    wrapMargin = settings1.value("editor/wrapMargin");
    tabSize = settings1.value("editor/tabSize");
    userName = settings1.value("user/name");
    userEmail = settings1.value("user/email");

    std::cout << std::endl << std::endl;
    std::cout << "Updated configuration:\n";
    std::cout << "editor/wrapMargin: " << wrapMargin << std::endl;
    std::cout << "editor/tabSize: " << tabSize << std::endl;
    std::cout << "user/name: " << userName << std::endl;
    std::cout << "user/email: " << userEmail << std::endl;

    return 0;
}
