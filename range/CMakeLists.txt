cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(range CXX)

add_executable(range range_test.cpp)
target_link_libraries(range gtest)

add_test(Range range)
