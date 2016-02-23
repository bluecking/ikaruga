# Setup sources
set(XML_SOURCES
        XML.cpp)

# Build executable
add_executable(xml ${XML_SOURCES})
target_link_libraries(xml ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY})
target_link_libraries(xml m)
target_link_libraries(xml ${Boost_LIBRARIES})