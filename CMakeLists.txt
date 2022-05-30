cmake_minimum_required(VERSION 3.12)

project(AGCPlusPlus VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED False)

# Generate the "main.h" file with #defines for the version numbers
configure_file(src/main.hpp.in generated_src/main.hpp)

add_executable(AGCPlusPlus src/main.cpp src/agc.cpp src/memory.cpp src/cpu.cpp)

target_include_directories(AGCPlusPlus PUBLIC
                           "${PROJECT_BINARY_DIR}/generated_src"
                           )
