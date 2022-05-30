# Stick with relatively recent CMake versions
cmake_minimum_required(VERSION 3.12)

# Define the project and version
project(AGCPlusPlus VERSION 0.1)

# Let's try to take advantage of the latest C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED False)

# Generate the "main.h" file with #defines for the version numbers
configure_file(src/main.hpp.in generated_src/main.hpp)

# Set a variable containing the list of source files, to avoid cluttering our add_executable() statement
set(SOURCES src/main.cpp src/agc.hpp src/agc.cpp src/memory.hpp src/memory.cpp src/cpu.hpp src/cpu.cpp)

# Define the project target
add_executable(AGCPlusPlus ${SOURCES})

# Add the extra generated header file for our version number
target_include_directories(AGCPlusPlus PUBLIC
                           "${PROJECT_BINARY_DIR}/generated_src"
                           )
