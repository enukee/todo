cmake_minimum_required (VERSION 3.8)
project (helloworld)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(helloworld main.cpp mainwindow.cpp mainwindow.h imgwidget.cpp imgwidget.h ImageView.cpp ImageView.h)

target_link_libraries(helloworld
        Qt5::Widgets
        Qt5::Gui
        Qt5::QWindowsIntegrationPlugin)  
