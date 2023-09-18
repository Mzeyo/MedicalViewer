cmake_minimum_required(VERSION 3.16)

project(MedicalDemo)

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  FiltersCore
  FiltersModeling
  IOImage
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  RenderingVolume
  RenderingVolumeOpenGL2
)

find_package(Qt5 COMPONENTS Widgets REQUIRED QUIET)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "MedicalDemo: Unable to find the VTK build folder.")
endif()

set(CMAKE_AUTOMOC ON)

# support for out-of-source build
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR} 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${VTK_INCLUDE_DIRS}
)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        MarchingCube.cpp
        MarchingCube.h
        OpenDICOMSeries.cpp
        OpenDICOMSeries.h
        VolumeRendering.cpp
        VolumeRendering.h
)

set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(MedicalDemo ${PROJECT_SOURCES})
target_link_libraries(MedicalDemo ${VTK_LIBRARIES})

TARGET_LINK_LIBRARIES( MedicalDemo Qt5::Core Qt5::Gui Qt5::Widgets)

vtk_module_autoinit(
    TARGETS MedicalDemo
    MODULES ${VTK_LIBRARIES}
)