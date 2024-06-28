cmake_minimum_required(VERSION 3.10)
project(MyProject)

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

add_subdirectory(libs/rapidyaml)

add_executable(csettings_app csettings.cpp)
target_link_libraries(csettings_app ryml)

add_custom_target(run
    COMMAND $<TARGET_FILE:csettings_app>
    DEPENDS csettings_app)
