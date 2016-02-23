project(JUMPER)
 
# States that CMake required version must be greater than 2.6
cmake_minimum_required(VERSION 2.8)
 
# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${JUMPER_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})
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

add_subdirectory(src/game)

cmake_minimum_required(VERSION 2.6)
PROJECT(LevelView)
 
set(JUMPER_SOURCES
	src/editor/Main.cpp
	src/editor/MainWindow.cpp
	src/editor/LevelScene.cpp
	src/editor/GraphicsTileItem.cpp
	src/editor/TextureScene.cpp
	src/editor/TextureScene.h
	src/editor/Settings.cpp
	src/editor/Settings.h)


FIND_PACKAGE(Qt4 REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE(${QT_USE_FILE})


QT4_WRAP_UI(UISrcs src/editor/LevelView.ui)
QT4_WRAP_CPP(MOCSrcs build/ui_LevelView.h )

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
 
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(LevelView ${JUMPER_SOURCES} ${MOCSrcs} ${UISrcs})
TARGET_LINK_LIBRARIES(LevelView ${QT_LIBRARIES})



