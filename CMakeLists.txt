# Stick with relatively recent CMake versions
cmake_minimum_required(VERSION 3.12)

# Define the project and version
project(AGCPlusPlus VERSION 0.5)

# Let's try to take advantage of the latest C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generate the "main.h" file with #defines for the version numbers
configure_file(src/main.hpp.in generated_src/main.hpp)

# Set a variable containing the list of source files, to avoid cluttering our add_executable() statement
set(SOURCES src/main.cpp
        src/common/global_definitions.hpp
        src/common/util_functions.hpp
        src/common/util_functions.cpp

        src/block1/block1defs.hpp
        src/block1/agc.cpp src/block1/agc.hpp
        src/block1/timer.cpp src/block1/timer.hpp
        src/block1/memory.cpp src/block1/memory.hpp
        src/block1/scaler.cpp src/block1/scaler.hpp
        src/block1/cpu.cpp src/block1/cpu.hpp
        src/block1/subinstructions.cpp src/block1/subinstructions.hpp
        src/block1/control_pulses.cpp src/block1/control_pulses.hpp

        src/block2/block2defs.hpp
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
FetchContent_Declare(
        sockpp
        GIT_REPOSITORY https://github.com/fpagliughi/sockpp.git
        GIT_TAG v0.8.2
)
FetchContent_MakeAvailable(sockpp)

# Define the project target
add_executable(AGCPlusPlus ${SOURCES})

# Link our libraries
target_link_libraries(AGCPlusPlus PUBLIC argparse)
target_link_libraries(AGCPlusPlus PUBLIC sockpp)

# Add the extra generated header file for our version number
target_include_directories(AGCPlusPlus PUBLIC
                           "${PROJECT_BINARY_DIR}/generated_src"
                           )

# If on Windows, copy the sockpp DLL to the executable directory because Windows can't find it otherwise.
if(WIN32)
    # Uncomment only one, or add your own if your environment calls the DLL something else.
    set(SOCKPP_DLL_NAME libsockpp.dll)  # For CLion
    #set(SOCKPP_DLL_NAME sockpp.dll)     # For Visual Studio

    file(COPY ${sockpp_BINARY_DIR}/${SOCKPP_DLL_NAME}
        DESTINATION ${PROJECT_BINARY_DIR})
endif()
