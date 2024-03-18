cmake_minimum_required(VERSION 3.21)
project(LabNow)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE SRC_TESTS tests/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SRC} ${SRC_TESTS})