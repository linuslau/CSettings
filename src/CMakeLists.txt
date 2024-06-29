
option(BUILD_SHARED_LIB "Build as a shared library (DLL)" ON)

if(BUILD_SHARED_LIB)
    # Define the library
    add_library(Settings SHARED Settings.cpp)
    set_target_properties(Settings PROPERTIES OUTPUT_NAME "settings")
else()
    # Define the library
    add_library(Settings STATIC Settings.cpp)
    set_target_properties(Settings PROPERTIES OUTPUT_NAME "settings")
endif()

# Include directories
target_include_directories(Settings PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/libs/rapidyaml/src)

# Link rapidyaml with the library
target_link_libraries(Settings ryml)

if(BUILD_SHARED_LIB)
	# Add post-build commands to copy DLL to testapp directory, if project is configured by command line
	add_custom_command(TARGET Settings POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:Settings> ${CMAKE_BINARY_DIR}/testapp/$<CONFIGURATION>/$<TARGET_FILE_NAME:Settings>
		COMMENT "Copying Settings.dll to testapp directory"
	)

	# Add post-build commands to copy DLL to testapp directory, if project is configured by Visual Studio
	add_custom_command(TARGET Settings POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:Settings> ${CMAKE_BINARY_DIR}/testapp/$<TARGET_FILE_NAME:Settings>
		COMMENT "Copying Settings.dll to testapp directory"
	)
endif()