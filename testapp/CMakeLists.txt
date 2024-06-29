# Create executable
add_executable(SettingsTest main.cpp)

# Include directories
target_include_directories(SettingsTest PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/libs/rapidyaml/include)  # Ìí¼Ó include Â·¾¶

# Link the library and rapidyaml with the executable
target_link_libraries(SettingsTest PRIVATE Settings ryml)