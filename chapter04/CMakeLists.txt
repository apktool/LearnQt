cmake_minimum_required(VERSION 3.16)
project(charactermap LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(charactermap
    main.cc
    src/character_widget.h src/character_widget.cc
    src/main_window.h src/main_window.cc
    )

set_target_properties(charactermap PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    )

target_link_libraries(charactermap PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    )
