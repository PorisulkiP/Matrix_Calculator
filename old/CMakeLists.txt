cmake_minimum_required(VERSION 3.5)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(calculator)

set(HEADERS
    operations.h)

set(
    MatrixCalculator.cpp
    operations.cpp
)

add_executable(MatrixCalculator ${HEADERS} ${SOURCES})

set_target_properties(MatrixCalculator PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
