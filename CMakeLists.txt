cmake_minimum_required(VERSION 2.8)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(FindCXX11)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(googletest/googletest)
endif()

add_subdirectory(biginteger)
add_subdirectory(range)
add_subdirectory(statistics)
