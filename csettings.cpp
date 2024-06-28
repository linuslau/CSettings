#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "ryml.hpp"
#include "ryml_std.hpp"

void print_yaml_node(const ryml::ConstNodeRef& node, int indent = 0) {
    std::string indent_str(indent, ' ');

    if (node.is_map()) {
        for (const auto& child : node) {
            std::cout << indent_str << child.key() << ":";
            if (child.has_val()) {
                std::cout << " " << child.val() << "\n";
            }
            else {
                std::cout << "\n";
            }
            print_yaml_node(child, indent + 2);
        }
    }
    else if (node.is_seq()) {
        for (const auto& child : node) {
            std::cout << indent_str << "-";
            if (child.has_val()) {
                std::cout << " " << child.val() << "\n";
            }
            else {
                std::cout << "\n";
            }
            print_yaml_node(child, indent + 2);
        }
    }
    else if (node.is_val()) {
        std::cout << indent_str << node.val() << "\n";
    }
}

int test_parse_yaml_file() {

    std::ifstream file("config.yaml");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string yaml_str = buffer.str();


    ryml::Tree tree = ryml::parse_in_place(ryml::to_substr(yaml_str));

    print_yaml_node(tree.rootref());

    return 0;
}

void test_serialized()
{
    ryml::Tree tree = ryml::parse_in_arena("{a: b}");

    ryml::NodeRef root = tree.rootref();

    root["a"].set_val_serialized(12345);

    std::string node_value = root["a"].val().str;
    std::cout << "Node 'a' value after set_val_serialized: " << node_value << std::endl;
}

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

    ~Settings() {
        // save();
        std::cout << "Settings object for file \"" << filename_ << "\" is being destroyed." << std::endl;
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
                    std::cout << "  Child node is present: " << token;
                    node = node[token.c_str()];
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
                std::cerr << "  Token is empty, ignore this iteration." << std::endl;
            }
        }

        if (!has_diff && !overwrite)
        {
            std::cerr << "  NOT overwrite." << std::endl;
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

    void setValues(const std::string& path, const std::vector<std::pair<std::string, std::string>>& keyValues, bool overwrite = true) {
        for (const auto& kv : keyValues) {
            setValue(path + "/" + kv.first, kv.second, overwrite);
        }
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

    //test_serialized();
    //test_parse_yaml_file();

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

    settings.setValue("/editor/wrapMargin", "100");
    settings.setValue("/editor/wrapMargin/xxx/yyy/zzz", "1111111111", false);
    settings.setValue("/editor/tabSize", "200");
    settings.setValue("/user/name", "Fokatu");
    settings.setValue("/user/email", "Fokatu@Fokatu.com");
    settings.setValue("/uuuu/vvvv/www/xxx/yyy/zzz", "2222222222");
    settings.setValue("/uuuu/vvvv/aaa/xxx/yyy/zzz", "3333333333");

    std::string wrapMargin = settings.value("/editor/wrapMargin");
    std::string tabSize = settings.value("/editor/tabSize");
    std::string userName = settings.value("/user/name");
    std::string userEmail = settings.value("/user/email");

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


    Settings settings2(filename);
    std::vector<std::pair<std::string, std::string>> keyValues = {
        {"wrapMargin2", "200"},
        {"wrapMargin3", "300"},
        {"wrapMargin4", "400"},
        {"wrapMargin5", "500"},
    };

    settings2.setValues("/editor", keyValues);
    settings2.save();

    //
    {
        std::cout << "=============================================================" << std::endl;
        std::cout << "Test Multiple Slash" << std::endl;
        std::cout << "=============================================================" << std::endl;
        Settings settings10(filename);
        settings10.setValue("////aaaa///bbbb", "cccc");
        settings10.save();
    }

    //
    {
        std::cout << "=============================================================" << std::endl;
        std::cout << "Test " << std::endl;
        std::cout << "=============================================================" << std::endl;
        Settings settings10(filename);
        settings10.setValue("////aaaa", "cccc");
        settings10.save();
    }

    //
    {
        std::cout << "=============================================================" << std::endl;
        std::cout << "Test " << std::endl;
        std::cout << "=============================================================" << std::endl;
        Settings settings10(filename);
        settings10.setValue("////bbbb///", "cccc");
        settings10.save();
    }

    //
    {
        std::cout << "=============================================================" << std::endl;
        std::cout << "Test " << std::endl;
        std::cout << "=============================================================" << std::endl;
        Settings settings10(filename);
        settings10.setValue("a\b\c", "cccc");
        settings10.save();
    }

    return 0;
}
