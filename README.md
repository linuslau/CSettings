# CSettings

- [CSettings](#csettings)
  - [Purpose](#purpose)
  - [Project structure](#project-structure)
  - [Build command](#build-command)
  - [Run sample app](#run-sample-app)
  - [Project Introduction](#project-introduction)
  - [Features](#features)
  - [Contribution](#contribution)

## Purpose
With C++, To simplify the usage of YAML as a config file, similar to [QSettings](https://doc.qt.io/qt-6/qsettings.html), you can read/write tree-like key/value pairs easily. Here's an approach you can take:

```cpp
#include "Settings.hpp"
Settings settings("config.yml");
settings.setValue("/database/connection/retry/attempts", "5");
std::string retryAttempts = settings.value("/database/connection/retry/attempts");
settings.save();
```
Check config.yml result as below.
```
database:
  connection:
    retry:
      attempts: 5
```

Check testapp/main.cpp for more.

## Project structure
```
CSettings/
├── include/
│   └── Settings.hpp
├── src/
│   ├── CMakeLists.txt
│   └── Settings.cpp
├── libs/
│   └── rapidyaml/
├── testapp/
│   ├── CMakeLists.txt
│   └── main.cpp
├── CMakeLists.txt
```

## Build command

```
cd CSettings
cmake -G "Visual Studio 17 2022" -A x64 -B outs
cmake --build out --config Release
```

## Run sample app
```
cd out/testapp/Release/
SettingsTest.exe
```

## Project Introduction

Welcome to the GitHub page of this project!

I have always enjoyed using YAML for data configuration, and RapidYAML has been my favorite library for this purpose. It strikes a perfect balance in size, ease of use, and well-documented code examples. However, I wished it could be even more convenient because, in most cases, data configuration involves simple read and write operations.

When I came across QSettings from my friend Fokatu, I was impressed by its simplicity and efficiency. It got me thinking: what if we could handle YAML in the same way as QSettings? This idea of operating on YAML with a similar API, especially for reading and writing hierarchical structures, seemed not only interesting but also highly practical. Imagine how convenient it would be to write something like setValue(xxx/yyy/zzz, 'foo') and read it back effortlessly.

The goal of this project is to provide an API that mimics QSettings, allowing for easy reading and writing of YAML files, with robust support for hierarchical data structures. I hope this project can help you in your endeavors, and I welcome any suggestions or contributions!

## Features

Simple API: An interface similar to QSettings for intuitive usage
Hierarchical Structure Support: Easily read and write nested data
Powered by RapidYAML: Leverage the excellent YAML parsing capabilities

## Contribution

Feel free to submit Issues and Pull Requests. Let's improve this project together!

___

Thank you for visiting, and I look forward to your feedback and contributions!
