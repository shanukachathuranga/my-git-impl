cmake_minimum_required(VERSION 3.31)
project(mgit)

set(CMAKE_CXX_STANDARD 20)

# Find zlib package
find_package(ZLIB REQUIRED)

add_executable(mgit main.cpp zlib_utils.cpp)

# Include zlib headers
include_directories(${ZLIB_INCLUDE_DIRS})

# Link against zlib
target_link_libraries(mgit ${ZLIB_LIBRARIES})