############ XML Lib ##########
PROJECT(XML)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_library(xml SHARED src/xml/XML.cpp)
target_link_libraries(xml ${Boost_LIBRARIES})

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

enable_testing()
set(XMLTEST_DEPENDENCIES
    xml
    )
set(params /home/patrick/Git-Repositories/uni_hausaufgaben/praktikum1/res/levels/level0.xml)
add_executable(xmlTest src/xml/XmlTest.cpp src/xml/XML.hpp)
target_link_libraries(xmlTest ${XMLTEST_DEPENDENCIES})
configure_file(res/levels/level0.xml level0.xml COPYONLY)
add_test(NAME ScrollerTest COMMAND xmlTest level0.xml)

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
#set(EDITOR_LIBS ${EDITOR_LIBS} xml)
