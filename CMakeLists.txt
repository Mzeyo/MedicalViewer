cmake_minimum_required(VERSION 3.5)

project(Qt_image)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_MODULE_USE_QTXML true)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

find_package(VTK REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ReadDICOMSeries.h
        ReadDICOMSeries.cpp
)

include_directories(${VTK_INCLUDE_DIRS})

add_executable(Qt_image
            ${PROJECT_SOURCES}
        )

target_link_libraries(Qt_image Qt5::Widgets Qt5::Gui Qt5::Core)

target_link_libraries(Qt_image ${VTK_LIBRARIES})

vtk_module_autoinit(
    TARGETS Qt_image
    MODULES ${VTK_LIBRARYS}
)