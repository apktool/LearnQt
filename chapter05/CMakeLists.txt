cmake_minimum_required(VERSION 3.16)
project(codeeditor LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(codeeditor
    src/code_editor.cc src/code_editor.h main.cc
    )

set_target_properties(codeeditor PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    )

target_link_libraries(codeeditor PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    )
