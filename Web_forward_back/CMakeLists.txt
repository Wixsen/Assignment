cmake_minimum_required(VERSION 3.28)

project(test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(test main.cpp dList.hpp)
