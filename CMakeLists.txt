# Stick with relatively recent CMake versions
cmake_minimum_required(VERSION 4.0)

# Define the project and version
project(AGCPlusPlus VERSION 1.0)

# Let's try to take advantage of the latest C++ standards
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get my IDE (neovim) to recognize includes and libraries properly
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set a variable containing the list of source files, to avoid cluttering our add_executable() statement
set(SOURCES 
  main.cpp
)

# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

# Define the project target
add_executable(AGCPlusPlus ${SOURCES})

# Link our libraries
target_link_libraries(AGCPlusPlus PUBLIC argparse)

# Add the extra generated header file for our version number
target_include_directories(AGCPlusPlus PUBLIC
  "${PROJECT_BINARY_DIR}/generated_src"
)
