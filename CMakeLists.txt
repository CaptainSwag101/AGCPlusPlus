cmake_minimum_required(VERSION 3.12)

project(AGCPlusPlus VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(src/main.h.in generated_src/main.h)

add_executable(AGCPlusPlus src/main.cpp)

target_include_directories(AGCPlusPlus PUBLIC
                           "${PROJECT_BINARY_DIR}/generated_src"
                           )
