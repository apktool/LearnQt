cmake_minimum_required(VERSION 3.22)
project(icon)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/li/Software/qt-6.4.2/6.4.2/gcc_64")

find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

LIST(APPEND code_dir src)
FOREACH (folder ${code_dir})
  FILE(GLOB code_srcs ${folder}/*.cc)
  FILE(GLOB code_headers ${folder}/*.h)
ENDFOREACH ()

ADD_LIBRARY(libicon OBJECT ${code_headers} ${code_srcs})
TARGET_LINK_LIBRARIES(libicon
    Qt::Core
    Qt::Gui
    Qt::Widgets
    )

ADD_EXECUTABLE(icon main.cc)
TARGET_LINK_LIBRARIES(icon libicon)
