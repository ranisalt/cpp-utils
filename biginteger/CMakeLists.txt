cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(biginteger CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
find_package(GMP REQUIRED)

add_executable(biginteger biginteger.cpp biginteger_test.cpp)
include_directories(${GMP_INCLUDE_DIR})
target_link_libraries(biginteger gtest ${GMP_LIBRARY})

add_test(BigInteger biginteger)
