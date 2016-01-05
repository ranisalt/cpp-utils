cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(range)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -lgtest -std=c++14")

add_executable(range range_test.cpp)
include_directories(${GMP_INCLUDE_DIR})
target_link_libraries(range ${GMP_LIBRARY})
