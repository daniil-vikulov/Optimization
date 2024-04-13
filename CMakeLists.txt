cmake_minimum_required(VERSION 3.22)
project(LabNow)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSL REQUIRED gsl)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE SRC_TESTS tests/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SRC} ${SRC_TESTS}
        include/physics/Simulator.h
        src/Simulator.cpp
        include/maths/RKF45Integrator.h
        src/RKF45Integrator.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${GSL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GSL_LIBRARIES})

target_compile_options(${PROJECT_NAME} PRIVATE ${GSL_CFLAGS_OTHER})