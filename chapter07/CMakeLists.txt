cmake_minimum_required(VERSION 3.22)
project(chapter07)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

add_executable(chapter07 main.cc login.h login.cc login.ui)
target_link_libraries(chapter07
    Qt::Core
    Qt::Gui
    Qt::Widgets
    )
