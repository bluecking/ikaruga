cmake_minimum_required(VERSION 2.8)

project(xml)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Build library
add_library(xml SHARED XML.cpp)
target_link_libraries(xml ${Boost_LIBRARIES})
