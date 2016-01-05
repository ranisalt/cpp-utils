cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(mbi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -lgtest -lgmp -std=c++14")
find_package(GMP REQUIRED)

set(SOURCE_FILES main.cpp mbi.cpp mbi_test.cpp)
add_executable(mbi mbi.cpp mbi_test.cpp)
include_directories(${GMP_INCLUDE_DIR})
target_link_libraries(mbi ${GMP_LIBRARY})
