# Create executable
add_executable(SettingsTest main.cpp)

# Include directories
target_include_directories(SettingsTest PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/libs/rapidyaml/include)  # ���� include ·��

# Link the library and rapidyaml with the executable
target_link_libraries(SettingsTest PRIVATE Settings ryml)