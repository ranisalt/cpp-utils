cmake_minimum_required(VERSION 2.8)

project(biginteger CXX)

find_package(GMP REQUIRED)
include_directories(${GMP_INCLUDE_DIR})

add_library(biginteger biginteger.cpp)
target_link_libraries(biginteger ${GMP_LIBRARY})

if(BUILD_TESTING)
    add_executable(biginteger_test biginteger_test.cpp)
    target_link_libraries(biginteger_test biginteger gtest)

    add_test(BigInteger biginteger_test)
endif()
