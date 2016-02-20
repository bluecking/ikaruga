# Setup sources
set(JUMPER_SOURCES
    Actor.cpp
    AnimatedRenderable.cpp
    Bot.cpp
    Camera.cpp
    Collision.cpp
    Game.cpp
    Item.cpp
    Level.cpp
    Main.cpp
    MainWindow.cpp
    Network.cpp
    Player.cpp
    PlayerProperty.cpp
    Path.cpp
    PathPlanner.cpp
    PathFollower.cpp
    Renderable.cpp
    ScoreBoard.cpp	
    SparseMatrix.cpp
    SparseVector.cpp
    StaticRenderable.cpp
    TextureFactory.cpp
    TexturedLayer.cpp
    WorldProperty.cpp)

# Build executable
add_executable(jumper ${JUMPER_SOURCES})
target_link_libraries(jumper ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY})
target_link_libraries(jumper m)
target_link_libraries(jumper ${Boost_LIBRARIES})