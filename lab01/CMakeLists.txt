cmake_minimum_required(VERSION 3.22)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)

include_directories(external/include)
include_directories(include)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE SRC_TESTS tests/*.cpp)

add_executable(lab1 main.cpp ${SRC} ${SRC_TESTS}
        include/GccConsts.h
        tests/Functions.h)