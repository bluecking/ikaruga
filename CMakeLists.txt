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
add_subdirectory(src/xml)

set( QT_USE_QTOPENGL TRUE )
set( QT_USE_XML TRUE)
find_package( Qt4 )
if( QT4_FOUND )
    include_directories(${QT_INCLUDE_DIR})
    include_directories(${QT_QTGUI_INCLUDE_DIR})
    include_directories(${QT_QTOPENGL_INCLUDE_DIR})
    include_directories(${QT_QTCORE_INCLUDE_DIR})
    include_directories(${QT_QTXML_INCLUDE_DIR})
    
    add_subdirectory(src/editor)    
endif(QT4_FOUND)


