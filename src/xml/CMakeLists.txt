# Setup sources
set(XML_SOURCES
        XML.cpp
        XmlTest.cpp)


# Build executable
add_executable(xmlTest ${XML_SOURCES})
target_link_libraries(xmlTest ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY})
target_link_libraries(xmlTest m)
target_link_libraries(xmlTest ${Boost_LIBRARIES})

configure_file(../../res/levels/level0.xml level0.xml)
