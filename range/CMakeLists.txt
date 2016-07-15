cmake_minimum_required(VERSION 2.8)

project(range CXX)

add_library(range OBJECT range.cpp)

if(BUILD_TESTING)
    add_executable(range_test $<TARGET_OBJECTS:range> range_test.cpp)
    target_link_libraries(range_test gtest)

    add_test(Range range_test)
endif()
