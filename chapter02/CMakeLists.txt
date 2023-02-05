cmake_minimum_required(VERSION 3.22)
project(chapter02)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

add_executable(chapter02 main.cpp src/button.h src/button.cc src/window.h src/window.cc)
target_link_libraries(chapter02
    Qt::Core
    Qt::Gui
    Qt::Widgets
    )

