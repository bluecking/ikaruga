cmake_minimum_required(VERSION 2.6)
PROJECT(LevelView)
 
set(JUMPER_SOURCES
	src/Main.cpp
	src/MainWindow.cpp
	src/LevelScene.cpp
	src/GraphicsTileItem.cpp
		src/TextureScene.cpp src/TextureScene.h src/Settings.cpp src/Settings.h)


FIND_PACKAGE(Qt4 REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE(${QT_USE_FILE})


QT4_WRAP_UI(UISrcs src/LevelView.ui)
QT4_WRAP_CPP(MOCSrcs build/ui_LevelView.h )

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
 
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(LevelView ${JUMPER_SOURCES} ${MOCSrcs} ${UISrcs})
TARGET_LINK_LIBRARIES(LevelView ${QT_LIBRARIES})
