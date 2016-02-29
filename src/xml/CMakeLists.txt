# Build library
add_library(xml SHARED XML.cpp)
target_link_libraries(xml ${Boost_LIBRARIES})

# For testing
set(XMLTEST_DEPENDENCIES xml)
add_executable(xmlTest XmlTest.cpp XML.hpp)
target_link_libraries(xmlTest ${XMLTEST_DEPENDENCIES})
add_test(NAME XML COMMAND xmlTest ${CMAKE_SOURCE_DIR}/res/levels/level0.xml)
