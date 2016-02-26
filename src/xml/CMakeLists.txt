# Build library
add_library(xml SHARED XML.cpp)
target_link_libraries(xml ${Boost_LIBRARIES})

# Testing section
# find_package(Boost REQUIRED)
# include_directories(${Boost_INCLUDE_DIRS})
# add_executable(xmlTest XmlTest.cpp XML.hpp XML.cpp)
