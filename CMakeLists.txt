cmake_minimum_required(VERSION 3.10)
project(codebase VERSION 0.4.3 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Organize output directories for Visual Studio
if(MSVC)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/base
    ${CMAKE_SOURCE_DIR}/include
)

# Main executable
add_executable(codebase src/main.c)

# Tests
enable_testing()
add_executable(test_macros test/test_macros.c)
add_executable(test_all test/test_all.c)

add_test(NAME test_macros COMMAND test_macros)
add_test(NAME test_all COMMAND test_all)

# Visual Studio solution folders
set_target_properties(codebase PROPERTIES FOLDER "app")
set_target_properties(test_macros PROPERTIES FOLDER "tests")
set_target_properties(test_all PROPERTIES FOLDER "tests")

# Custom target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS test_macros test_all
)

# Optional: Group all targets in ALL_BUILD for Visual Studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
