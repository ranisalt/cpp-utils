cmake_minimum_required(VERSION 2.8)

project(range CXX)

if(BUILD_TESTING)
    add_executable(range range_test.cpp)
    target_link_libraries(range gtest)

    add_test(Range range)
endif()
