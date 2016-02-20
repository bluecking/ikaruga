set(EDITOR_SOURCES 
	app/Main.cpp 
	app/EditorMainWindow.cpp
	widgets/GraphicsTileItem.cpp
	widgets/TilesetScene.cpp
	widgets/LevelScene.cpp
)

#####################################################################################
# Set uis
#####################################################################################

set(EDITOR_UIS
   ui/MainWindow.ui
)

#####################################################################################
# Set mocs
#####################################################################################

set(EDITOR_MOCS
   app/EditorMainWindow.hpp
)

#####################################################################################
# Setup dependencies
#####################################################################################

set(EDITOR_DEPENDENCIES
	${QT_QTCORE_LIBRARIES} 
	${QT_QTGUI_LIBRARIES}  
	${QT_QTOPENGL_LIBRARIES} 
	${QT_QTXML_LIBRARY}  
)


qt_wrap_ui(editor EDITOR_UI_HDRS EDITOR_UI_SRC ${EDITOR_UIS})
qt_wrap_cpp(editor EDITOR_MOC_SRC ${EDITOR_MOCS})
add_definitions(${QT_DEFINITIONS})

#####################################################################################
# Add current binary dir to includes to find the generated header files
#####################################################################################

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#####################################################################################
# Add main executable
#####################################################################################

add_executable(editor ${EDITOR_SOURCES} ${EDITOR_MOC_SRC} ${EDITOR_UI_HDRS})
target_link_libraries(editor ${EDITOR_DEPENDENCIES})