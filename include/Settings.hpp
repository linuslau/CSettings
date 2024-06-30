#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <filesystem>
#include <stdexcept>
#include "ryml.hpp"
#include "ryml_std.hpp"
#include <windows.h>

#ifdef DEBUG_MODE
    #define DEBUG_LOG(x) std::cout << x << std::endl
#else
    #define DEBUG_LOG(x)
#endif

class Settings {
public:
    Settings();
    Settings(const std::string& filename);
    ~Settings();

    void setValue(const std::string& path, const std::string& value, bool overwrite = true);
    void setValues(const std::string& path, const std::vector<std::pair<std::string, std::string>>& keyValues, bool overwrite = true);
    std::string value(const std::string& path, const std::string& default_value = "");
    void save();
    bool delete_file(const std::string &filename = "");
    int  parseYamlFile(const std::string &filename = "");
    bool Settings::isValid() const;
    std::string Settings::getLastError() const;

private:
    void initialize(const std::string& filename);
    c4::yml::NodeRef getNode(const std::string& path);
    std::string getLastErrorAsString();
    void printYamlNode(const ryml::ConstNodeRef& node, int indent = 0);
    void testSerialized();

    std::string filename_;
    std::string buffer_;
    ryml::Tree tree_;
    bool valid_;
    std::string lastError_;
};

#endif // SETTINGS_H
