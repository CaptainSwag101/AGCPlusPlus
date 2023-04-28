# Stick with relatively recent CMake versions
cmake_minimum_required(VERSION 3.12)

# Define the project and version
project(AGCPlusPlus VERSION 0.2)

# Let's try to take advantage of the latest C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generate the "main.h" file with #defines for the version numbers
configure_file(src/main.hpp.in generated_src/main.hpp)

# Set a variable containing the list of source files, to avoid cluttering our add_executable() statement
set(SOURCES src/main.cpp src/globaldefs.hpp src/agc.hpp src/agc.cpp src/memory.hpp src/memory.cpp src/cpu.hpp src/cpu.cpp src/control_pulses.hpp src/control_pulses.cpp src/subinstructions.hpp src/subinstructions.cpp src/timer.hpp src/timer.cpp src/scaler.hpp src/scaler.cpp)

# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)
FetchContent_Declare(
        sockpp
        GIT_REPOSITORY https://github.com/fpagliughi/sockpp.git
)
FetchContent_MakeAvailable(sockpp)

# Define the project target
add_executable(AGCPlusPlus ${SOURCES})

# Search for the sockpp library
#find_library(LIBSOCKPP sockpp)
target_link_libraries(AGCPlusPlus PUBLIC sockpp)
target_link_libraries(AGCPlusPlus PUBLIC argparse)

# Add the extra generated header file for our version number
target_include_directories(AGCPlusPlus PUBLIC
                           "${PROJECT_BINARY_DIR}/generated_src"
                           )
