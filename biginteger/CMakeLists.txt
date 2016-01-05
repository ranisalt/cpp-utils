cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(biginteger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
find_package(GMP REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(biginteger biginteger.cpp biginteger_test.cpp)
include_directories(${GMP_INCLUDE_DIR} ${GTEST_INCLUDE_DIRS})
target_link_libraries(biginteger ${GMP_LIBRARY} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_test(BigInteger biginteger)
