PROJECT(XML)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(xmlTest XmlTest.cpp XML.hpp XML.cpp)