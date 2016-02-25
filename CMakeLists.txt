################### GAME #################
project(SCROLLER)

# States that CMake required version must be greater than 2.6
cmake_minimum_required(VERSION 2.8)

# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${SCROLLER_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Find SDL2 libraries using the custom made module in
# the cmake/ path
find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(Boost REQUIRED)

# Add SDL2 include directory to search path
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMG_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

#REPLACES ADDING SOURCES
add_subdirectory(src/game)

############ EDITOR ##########

PROJECT(EDITOR)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

set(EDITOR_SOURCES 
	src/editor/Main.cpp 
	src/editor/EditorMainWindow.cpp
	src/editor/GraphicsTileItem.cpp
	src/editor/TilesetScene.cpp
	src/editor/LevelScene.cpp
)

set(EDITOR_UIS
   src/editor/MainWindow.ui
)

set(EDITOR_MOCS
   src/editor/EditorMainWindow.hpp
)

set(EDITOR_DEPENDENCIES
	${QT_QTCORE_LIBRARIES} 
	${QT_QTGUI_LIBRARIES}  
	${QT_QTOPENGL_LIBRARIES} 
	${QT_QTXML_LIBRARY}  
)


qt_wrap_ui(editor EDITOR_UI_HDRS EDITOR_UI_SRC ${EDITOR_UIS})
qt_wrap_cpp(editor EDITOR_MOC_SRC ${EDITOR_MOCS})
add_definitions(${QT_DEFINITIONS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(editor ${EDITOR_SOURCES} ${EDITOR_MOC_SRC} ${EDITOR_UI_HDRS})
target_link_libraries(editor ${EDITOR_DEPENDENCIES})

############ XML Lib ##########
PROJECT(XML)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_subdirectory(src/xml)