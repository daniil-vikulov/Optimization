cmake_minimum_required(VERSION 3.10)

project(test_bsm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIRS})
link_directories(${GSL_LIBRARY_DIRS})

set(SOURCES
    main.cpp
    tests/tests.cpp
    utils/utils.cpp
    maths/RKF45Integrator.cpp
    black_scholes/black_scholes_analytical.cpp
    black_scholes/black_scholes_numerical.cpp
)

add_executable(test_bsm ${SOURCES})

target_link_libraries(test_bsm
    ${GSL_LIBRARIES}
    m
)

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -rf CMakeFiles CMakeCache.txt Makefile cmake_install.cmake test_bsm
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning all build files"
)
