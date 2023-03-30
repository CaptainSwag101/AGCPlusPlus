# Stick with relatively recent CMake versions
cmake_minimum_required(VERSION 3.12)

# Define the project and version
project(AGCPlusPlus VERSION 0.3)

# Let's try to take advantage of the latest C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generate the "main.h" file with #defines for the version numbers
configure_file(src/main.hpp.in generated_src/main.hpp)

# Set a variable containing the list of source files, to avoid cluttering our add_executable() statement
set(SOURCES src/main.cpp
        src/block2/globaldefs.hpp
        src/block2/agc.hpp src/block2/agc.cpp
        src/block2/memory.hpp src/block2/memory.cpp
        src/block2/cpu.hpp src/block2/cpu.cpp
        src/block2/control_pulses.hpp src/block2/control_pulses.cpp
        src/block2/subinstructions.hpp src/block2/subinstructions.cpp
        src/block2/timer.hpp src/block2/timer.cpp
        src/block2/scaler.hpp src/block2/scaler.cpp
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

# Search for the sockpp library
find_library(LIBSOCKPP sockpp)

# Link our libraries
target_link_libraries(AGCPlusPlus PUBLIC "${LIBSOCKPP}")
target_link_libraries(AGCPlusPlus PUBLIC argparse)

# Add the extra generated header file for our version number
target_include_directories(AGCPlusPlus PUBLIC
                           "${PROJECT_BINARY_DIR}/generated_src"
                           )
