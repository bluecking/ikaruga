# Build library
add_library(xml SHARED XML.cpp)
target_link_libraries(xml ${Boost_LIBRARIES})

# For testing
set(XMLTEST_DEPENDENCIES xml)
add_executable(xmlTest XmlTest.cpp XML.hpp)
target_link_libraries(xmlTest ${XMLTEST_DEPENDENCIES})
configure_file(../../res/levels/level0.xml level0.xml COPYONLY)
add_test(NAME ScrollerTest COMMAND xmlTest level0.xml)