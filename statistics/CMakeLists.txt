cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(statistics CXX)

add_executable(statistics statistics_test.cpp)
target_link_libraries(statistics gtest)

add_test(Statistics statistics)
