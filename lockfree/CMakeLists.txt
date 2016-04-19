cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(lockfree CXX)

add_executable(lockfree stack_test.cpp)
target_link_libraries(lockfree gtest)

add_test(Lockfree lockfree)
