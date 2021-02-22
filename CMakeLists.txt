cmake_minimum_required(VERSION 3.16)
project(start_svm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER gcc-10.2)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")

include_directories(include)

file(GLOB SRC_FILES mfcc.cpp)
add_library(mfcc ${SRC_FILES})

add_executable(start_svm main.cpp)
target_link_libraries(start_svm tbb fftw3)
target_link_libraries(start_svm mfcc)
