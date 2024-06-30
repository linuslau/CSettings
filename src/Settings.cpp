#include "Settings.h"
namespace fs = std::filesystem;

Settings::Settings(const std::string& filename) : filename_(filename), valid_(true) {
    std::ifstream file(filename_);
    if (!file.is_open()) {
        std::cerr << "File not found, creating a new file: " << filename_ << std::endl;
        std::ofstream new_file(filename_);
        if (!new_file.is_open()) {
            std::string error_message = getLastErrorAsString();
            std::cerr << "Failed to create file: " << filename_ << std::endl;
            std::cerr << "Error: " << error_message << std::endl;
            valid_ = false;
            lastError_ = "Failed to create file: " + filename_ + ", Error: " + error_message;
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
        valid_ = false;
        lastError_ = "Error parsing YAML: " + std::string(e.what());
        return;
    }

    if (!tree_.rootref().is_map()) {
        tree_.rootref() |= ryml::MAP; // Ensure root is a map
    }
}

Settings::~Settings() {
    // save();
#ifdef DEBUG_MODE    
    std::cout << "Settings object for file \"" << filename_ << "\" is being destroyed." << std::endl;
#endif
}

void Settings::setValue(const std::string& path, const std::string& value, bool overwrite) {
    std::cout << std::endl << "Setting value: " << value << " for path: " << path << std::endl;

    // Convert value to csubstr
    std::string value_copy = value;
    ryml::csubstr cstr_value = ryml::to_csubstr(value_copy);

    // Replace backslashes with forward slashes
    std::string modified_path = path;
    std::replace(modified_path.begin(), modified_path.end(), '\\', '/');

    // Split the path into tokens
    std::istringstream iss(modified_path);
    std::string token;
    auto node = tree_.rootref();
    bool has_diff = false;

    while (std::getline(iss, token, '/')) {
        if (!token.empty()) {
            if (!node.has_child(token.c_str())) {
                has_diff = true;
#ifdef DEBUG_MODE                
                std::cout << "  Child node is NOT present: " << token << std::endl;
#endif                
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
#ifdef DEBUG_MODE
                std::cout << "  Child node is present: " << token;
#endif                
                node = node[token.c_str()];
                if (overwrite) {
                    // node &= ryml::KEYVAL;
                    node.clear_flag(ryml::KEYVAL);
                    node |= ryml::KEYMAP;
                }
#ifdef DEBUG_MODE                
                std::cout << ", check child" << std::endl;
#endif                
            }
#ifdef DEBUG_MODE
            std::cout << "      Token: " << token << ", Node valid: " << node.valid()
                << ", Node is_map: " << node.is_map() << ", iss.eof(): " << iss.eof() << std::endl;
#endif            

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
#ifdef DEBUG_MODE            
            std::cout << "  Token is empty, ignore this iteration." << std::endl;
#endif
        }
    }

    if (has_diff || overwrite)
    {
#ifdef DEBUG_MODE        
        std::cout << "  has difference or need overwrite." << std::endl;
#endif        
        // Set the value for the final node
        node.clear_children();
        node.clear_flag(ryml::MAP);
        node |= ryml::VAL;
        node.set_val_serialized(cstr_value);
        //node.set_val(cstr_value);
    }

    return;
}

void Settings::setValues(const std::string& path, const std::vector<std::pair<std::string, std::string>>& keyValues, bool overwrite) {
    for (const auto& kv : keyValues) {
        setValue(path + "/" + kv.first, kv.second, overwrite);
    }
}

std::string Settings::value(const std::string& path, const std::string& default_value) {
    auto node = getNode(path);
    if (!node.empty()) {
        if (node.valid()) {
            if (node.is_val())
                std::cerr << "Node has value: " << path << std::endl;
            if (node.has_val()) {
                std::string node_value_tmp = node.val().str;
                std::string node_value = node_value_tmp.substr(0, node.val().size());
                size_t pos = node_value.find_first_of("\n ");
                if (pos != std::string::npos) {
                    node_value = node_value.substr(0, pos);
                }
                return node_value;
            }
            else {
                std::cerr << "Node has no value: " << path << std::endl;
                return default_value;
            }
        }
        else {
            std::cerr << "Invalid path" << path << std::endl;
            return default_value;
        }
    }
    else {
        std::cerr << "Invalid path, node not present: " << path << std::endl;
        return default_value;
    }
}

void Settings::save() {
    size_t len = 0;
#ifdef DEBUG_MODE
    std::cout << std::endl << "Saving settings to stdout" << std::endl;
    len = ryml::emit_yaml(tree_, tree_.root_id(), stdout);
#endif

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

bool Settings::delete_file(const std::string &filename) {
    std::string file_to_delete = filename.empty() ? filename_ : filename;
    try {
        if (fs::exists(file_to_delete)) {
            fs::remove(file_to_delete);
            std::cout << "File " << file_to_delete << " deleted successfully." << std::endl;
            return true;
        } else {
            std::cerr << "File " << file_to_delete << " does not exist." << std::endl;
            return false;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }
}

bool Settings::isValid() const {
    return valid_;
}

std::string Settings::getLastError() const {
    return lastError_;
}

c4::yml::NodeRef Settings::getNode(const std::string& path) {
    std::istringstream iss(path);
    std::string token;
    auto node = tree_.rootref();
    while (std::getline(iss, token, '/')) {
        if (!token.empty()) {
            if (!node.has_child(token.c_str())) {
                node[token.c_str()] = ryml::NodeRef{};
                break;
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

std::string Settings::getLastErrorAsString() {
    // Get the error code
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string(); // No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;
    // Convert the error code to a readable message
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);

    // Free the buffer allocated by FormatMessage
    LocalFree(messageBuffer);

    return message;
}

void Settings::printYamlNode(const ryml::ConstNodeRef& node, int indent) {
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
            printYamlNode(child, indent + 2);
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
            printYamlNode(child, indent + 2);
        }
    }
    else if (node.is_val()) {
        std::cout << indent_str << node.val() << "\n";
    }
}

int Settings::parseYamlFile(const std::string &filename) {

    std::string file_to_parse = filename.empty() ? filename_ : filename;

    std::ifstream file(file_to_parse);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file.\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string yaml_str = buffer.str();

    ryml::Tree tree = ryml::parse_in_place(ryml::to_substr(yaml_str));

    printYamlNode(tree.rootref());

    return 0;
}

void Settings::testSerialized()
{
    ryml::Tree tree = ryml::parse_in_arena("{a: b}");

    ryml::NodeRef root = tree.rootref();

    root["a"].set_val_serialized(12345);

    std::string node_value = root["a"].val().str;
    std::cout << "Node 'a' value after set_val_serialized: " << node_value << std::endl;
}
