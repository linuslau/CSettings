#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <filesystem>
#include "ryml.hpp"
#include "ryml_std.hpp"

#ifdef DEBUG_MODE
    #define DEBUG_LOG(x) std::cout << x << std::endl
#else
    #define DEBUG_LOG(x)
#endif

class Settings {
public:
    Settings(const std::string& filename);
    ~Settings();

    void setValue(const std::string& path, const std::string& value, bool overwrite = true);
    void setValues(const std::string& path, const std::vector<std::pair<std::string, std::string>>& keyValues, bool overwrite = true);
    std::string value(const std::string& path, const std::string& default_value = "");
    void save();
    bool delete_file(const std::string &filename = "");

private:
    c4::yml::NodeRef getNode(const std::string& path);
    void print_yaml_node(const ryml::ConstNodeRef& node, int indent = 0);
    int  test_parse_yaml_file();
    void test_serialized();

    std::string filename_;
    std::string buffer_;
    ryml::Tree tree_;
};

#endif // SETTINGS_H
