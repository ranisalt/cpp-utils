cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(skiplist CXX)

add_executable(skiplist skiplist_test.cpp)
target_link_libraries(skiplist gtest)

add_test(skiplist skiplist)
