cmake_minimum_required(VERSION 3.16)
project(start_svm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER gcc-10.2 )

set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(tools /opt/cross)
set(CMAKE_C_COMPILER ${tools}/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/aarch64-linux-gnu-g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3  -Wall -Wextra -std=c++20")

include_directories(include)
add_executable(start_svm main.cpp)
target_link_libraries(start_svm)
