cmake_minimum_required(VERSION 3.22)
project(test_all)
include(../CMakeLists.txt)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/naive/*.cpp)
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${src})
set(CMAKE_CXX_STANDARD 14)

add_executable(test_all test_all.cpp ${src})


