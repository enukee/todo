cmake_minimum_required (VERSION 3.8)
project (helloworld)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(helloworld "main.cpp" "mainwindow.cpp" "mainwindow.h" "imgwidget.cpp" "imgwidget.h" "ImageView.cpp" "ImageView.h" 
"InputField.h" "InputField.cpp" "processingWidget.cpp" "processingWidget.h" "coordinateInputPanel.cpp" "coordinateInputPanel.h" 
"bmp/BmpFile.cpp" "bmp/BmpFile.h" "bmp/ImageMatrix.cpp" "bmp/ImageMatrix.h" "bmp/pixel.h" "bmp/matrixProcessing.cpp" "bmp/matrixProcessing.h" 
"bmp/progressValue.cpp" "bmp/progressValue.h")

set_property(TARGET helloworld PROPERTY CXX_STANDARD 17)

target_link_libraries(helloworld
        Qt5::Widgets
        Qt5::Gui
        Qt5::QWindowsIntegrationPlugin
)  
