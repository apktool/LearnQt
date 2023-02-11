CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(calendarwidget LANGUAGES CXX)

SET(CMAKE_AUTOMOC ON)

IF (NOT DEFINED INSTALL_EXAMPLESDIR)
  SET(INSTALL_EXAMPLESDIR "examples")
ENDIF ()

FIND_PACKAGE(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

QT_ADD_EXECUTABLE(calendarwidget
    main.cpp
    # window.cpp window.h
    src/windows.h src/windows.cc
    )

SET_TARGET_PROPERTIES(calendarwidget PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    )

TARGET_LINK_LIBRARIES(calendarwidget PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    )