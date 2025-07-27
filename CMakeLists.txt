cmake_minimum_required(VERSION 3.10)
project(codebase VERSION 0.4.3 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/base
    ${CMAKE_SOURCE_DIR}/include
)

# Main executable
add_executable(codebase 
	       src/main.c
)

# Debug build
set_target_properties(codebase PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release
)

# Tests
enable_testing()
add_executable(test_macros test/test_macros.c)
add_executable(test_all test/test_all.c)

# Link test_all with nothing (it just runs other tests)
# If you add more tests, add them here:
add_test(NAME test_macros COMMAND test_macros)
add_test(NAME test_all COMMAND test_all)

# Optionally, group all tests in a custom target
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS test_macros test_all
)
