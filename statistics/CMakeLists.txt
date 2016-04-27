cmake_minimum_required(VERSION 2.8)

project(statistics CXX)

if(BUILD_TESTING)
    add_executable(statistics statistics_test.cpp)
    target_link_libraries(statistics gtest)

    add_test(Statistics statistics)
endif()
