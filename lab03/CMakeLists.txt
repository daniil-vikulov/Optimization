cmake_minimum_required(VERSION 3.21)
project(LabNow)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSL REQUIRED gsl)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE SRC_TESTS tests/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SRC} ${SRC_TESTS})

target_include_directories(${PROJECT_NAME} PRIVATE ${GSL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GSL_LIBRARIES})

target_compile_options(${PROJECT_NAME} PRIVATE ${GSL_CFLAGS_OTHER})