cmake_minimum_required(VERSION 3.10)
project(MyProject)

add_subdirectory(libs/rapidyaml)

add_executable(csettings_app csettings.cpp)
target_link_libraries(csettings_app ryml)

add_custom_target(run
    COMMAND $<TARGET_FILE:csettings_app>
    DEPENDS csettings_app)
