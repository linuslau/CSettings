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
            std::cerr << "File not found, creating a new file: " << filename_ << std::endl;
            std::ofstream new_file(filename_);
            if (!new_file.is_open()) {
                std::cerr << "Failed to create file: " << filename_ << std::endl;
                return;
            }
            new_file.close();
        }
        else {
            std::string yaml_content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();
            buffer_ = yaml_content;
        }

        ryml::substr yaml_substr = ryml::to_substr(buffer_);
        try {
            tree_ = ryml::parse_in_place(yaml_substr);
        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing YAML: " << e.what() << std::endl;
            tree_ = ryml::Tree();
        }

        if (!tree_.rootref().is_map()) {
            tree_.rootref() |= ryml::MAP; // Ensure root is a map
        }
    }

    void setValue(const std::string& path, const std::string& value, bool overwrite = true) {
        std::cout << std::endl << "Setting value: " << value << " for path: " << path << std::endl;

        // Convert value to csubstr
        std::string value_copy = value;
        ryml::csubstr cstr_value = ryml::to_csubstr(value_copy);

        // Split the path into tokens
        std::istringstream iss(path);
        std::string token;
        auto node = tree_.rootref();
        bool has_diff = false;

        while (std::getline(iss, token, '/')) {
            if (!token.empty()) {
                if (!node.has_child(token.c_str())) {
                    has_diff = true;
                    std::cout << "  Child node is NOT present: " << token << std::endl;
                    auto child = node.append_child();
                    // Check if it is the last token; if so, set it as a value, otherwise keep it as a MAP
                    if (iss.eof()) {
                        child |= ryml::VAL;
                    }
                    else {
                        child |= ryml::MAP;
                    }
                    child.set_key_serialized(ryml::to_csubstr(token));
                    node = child;
                }
                else {
                    std::cout << "  Child node is present: " << token << std::endl;
                    node = node[token.c_str()];
                    std::cout << "overwrite = " << overwrite << std::endl;
                    if (overwrite) {
                        // node &= ryml::KEYVAL;
                        node.clear_flag(ryml::KEYVAL);
                        node |= ryml::KEYMAP;
                    }
                    std::cout << ", check child" << std::endl;
                }

                std::cout << "      Token: " << token << ", Node valid: " << node.valid()
                    << ", Node is_map: " << node.is_map() << ", iss.eof(): " << iss.eof() << std::endl;

                if (!node.valid()) {
                    std::cerr << "Invalid path segment: " << token << " (node is not valid)" << std::endl;
                    return;
                }
                else if (!node.is_map()) {
                    if (!iss.eof()) {
                        std::cerr << "Invalid path segment: " << token << " (node is not a map and not at end of path)" << std::endl;
                        return;
                    }
                }
            }
            else {
                std::cerr << "token is empty" << std::endl;
            }
        }

        if (!has_diff && !overwrite)
        {
            return;
        }

        // Set the value for the final node
        node.clear_children();
        node.clear_flag(ryml::MAP);
        node |= ryml::VAL;
        node.set_val_serialized(cstr_value);
        //node.set_val(cstr_value);
        return;
    }

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

        std::cout << std::endl << "Saving settings to stdout" << std::endl;
        size_t len = ryml::emit_yaml(tree_, tree_.root_id(), stdout);

        std::cout << std::endl << "Saving settings to file" << std::endl;

        FILE* file = std::fopen(filename_.c_str(), "w");
        if (!file) {
            std::cerr << "Failed to open file for saving: " << filename_ << std::endl;
            return;
        }

        len = ryml::emit_yaml(tree_, tree_.root_id(), file);
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

#if 0
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
#endif

    Settings settings(filename);

    settings.setValue("editor/wrapMargin", "100");
    settings.setValue("editor/wrapMargin/xxx/yyy/zzz", "1111111111", false);
    settings.setValue("editor/tabSize", "200");
    settings.setValue("user/name", "Fokatu");
    settings.setValue("user/email", "Fokatu@Fokatu.com");
    settings.setValue("uuuu/vvvv/www/xxx/yyy/zzz", "2222222222");
    settings.setValue("uuuu/vvvv/aaa/xxx/yyy/zzz", "3333333333");

    std::string wrapMargin = settings.value("editor/wrapMargin");
    std::string tabSize = settings.value("editor/tabSize");
    std::string userName = settings.value("user/name");
    std::string userEmail = settings.value("user/email");

    std::cout << "Updated configuration:\n";
    std::cout << "editor/wrapMargin: " << wrapMargin << std::endl;
    std::cout << "editor/tabSize: " << tabSize << std::endl;
    std::cout << "user/name: " << userName << std::endl;
    std::cout << "user/email: " << userEmail << std::endl;

    // 修改其中一个值并保存
    // settings.setValue("editor/wrapMargin", "100");
    // settings.setValue("editor/tabSize", "200");
    // settings.setValue("user/name", "Fokatu");
    // settings.setValue("user/email", "Fokatu@Fokatu.com");

    settings.save();


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
