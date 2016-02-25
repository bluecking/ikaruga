############ XML Lib ##########
PROJECT(XML)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
#add_subdirectory(src/xml)
add_library(xml SHARED src/xml/XML.cpp)
target_link_libraries(xml ${Boost_LIBRARIES})

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

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
#add_subdirectory(src/game)

set(SCROLLER_SOURCES
        src/game/Actor.cpp
        src/game/AnimatedRenderable.cpp
        src/game/Bot.cpp
        src/game/Camera.cpp
        src/game/Collidable.cpp
        src/game/Collision.cpp
        src/game/Game.cpp
        src/game/Item.cpp
        src/game/KillAnimation.cpp
        src/game/Level.cpp
        src/game/Main.cpp
        src/game/MainWindow.cpp
        src/game/Network.cpp
        src/game/Player.cpp
        src/game/PlayerProperty.cpp
        src/game/Path.cpp
        src/game/PathPlanner.cpp
        src/game/PathFollower.cpp
        src/game/PuzzleBox.cpp
        src/game/Renderable.cpp
        src/game/ScoreBoard.cpp
        src/game/SparseMatrix.cpp
        src/game/SparseVector.cpp
        src/game/StaticRenderable.cpp
        src/game/TextureFactory.cpp
        src/game/TexturedLayer.cpp
        src/game/WorldProperty.cpp
        src/game/Weapon.cpp
        src/game/Projectile.cpp
        src/game/LaserWeapon.cpp
        src/game/Armed.cpp)

set(SCROLLER_LIBS ${SCROLLER_LIBS} xml)

# Build executable
add_executable(scroller ${SCROLLER_SOURCES})
target_link_libraries(scroller ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY})
target_link_libraries(scroller m)
target_link_libraries(scroller ${Boost_LIBRARIES})
target_link_libraries(scroller ${SCROLLER_LIBS})

################## EDITOR ################
PROJECT(EDITOR)

set(EDITOR_SOURCES
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

add_executable(editor ${EDITOR_SOURCES} ${EDITOR_MOC_SRC} ${EDITOR_UI_HDRS})
target_link_libraries(editor ${EDITOR_DEPENDENCIES})
set(EDITOR_LIBS ${EDITOR_LIBS} xml)

