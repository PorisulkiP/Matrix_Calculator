cmake_minimum_required(VERSION 3.5)

project(matrixCalculator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES matrixCalculator_ru_RU.ts)


add_executable(matrixCalculator
                main.cpp
                mainwindow.cpp
                operations.cpp
                operations.h
                mainwindow.h
                mainwindow.ui
                button.cpp
                button.h
                ${TS_FILES}
)


target_link_libraries(matrixCalculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
