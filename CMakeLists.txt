cmake_minimum_required(VERSION 3.31)
project(mgit)

set(CMAKE_CXX_STANDARD 20)

add_executable(mgit main.cpp
        zlib_utils.cpp
        zlib_utils.h)
