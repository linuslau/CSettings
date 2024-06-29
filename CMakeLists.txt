cmake_minimum_required(VERSION 3.10)
# Set the project name
project(SettingsLibrary)

# Add debug mode option
option(DEBUG_MODE "Enable debug mode" ON)

# Settings.lib won't generated w/o this config.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Function to apply the patch if the submodule exists
function(apply_patch_if_exists)
    if(EXISTS "${CMAKE_SOURCE_DIR}/libs/rapidyaml/.github")
        execute_process(
            COMMAND git apply ${CMAKE_SOURCE_DIR}/libs/rapidyaml_clear_flag.patch
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/rapidyaml
            RESULT_VARIABLE result
        )
        if(result)
            message(WARNING "Failed to apply patch: rapidYAML_clear_flag.patch")
        else()
            message(STATUS "Patch applied successfully: rapidYAML_clear_flag.patch")
        endif()
    else()
        message(WARNING "rapidyaml submodule not found, skipping patch.")
    endif()
endfunction()

# Apply the patch before building the project
apply_patch_if_exists()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define preprocessor macro based on DEBUG_MODE option
if(DEBUG_MODE)
    add_definitions(-DDEBUG_MODE)
endif()

# Add subdirectories
add_subdirectory(libs/rapidyaml)
add_subdirectory(src)
add_subdirectory(testapp)
