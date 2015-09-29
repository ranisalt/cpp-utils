cmake_minimum_required(VERSION 2.8)
project(mbi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgtest -std=c++14")

set(SOURCE_FILES main.cpp mbi.cpp mbi_test.cpp)
add_executable(mbi ${SOURCE_FILES})
