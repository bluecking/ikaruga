# Setup sources
set(SCROLLER_SOURCES
        Actor.cpp
        AnimatedRenderable.cpp
        Bot.cpp
        Camera.cpp
        Collidable.cpp
        Collision.cpp
        Game.cpp
        Item.cpp
        KillAnimation.cpp
        Level.cpp
        Main.cpp
        MainWindow.cpp
        Network.cpp
        Player.cpp
        PlayerProperty.cpp
        Path.cpp
        PathPlanner.cpp
        PathFollower.cpp
        PuzzleBox.cpp
        Renderable.cpp
        StatusBar.cpp
        SparseMatrix.cpp
        SparseVector.cpp
        StaticRenderable.cpp
        TextureFactory.cpp
        TexturedLayer.cpp
        WorldProperty.cpp
        Weapon.cpp
        Projectile.cpp
        LaserWeapon.cpp
        Armed.cpp
        StatusBar.cpp)

set(SCROLLER_LIBS ${SCROLLER_LIBS} xml)

# Build executable
add_executable(scroller ${SCROLLER_SOURCES})
target_link_libraries(scroller ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY})
target_link_libraries(scroller m)
target_link_libraries(scroller ${Boost_LIBRARIES})
target_link_libraries(scroller ${SCROLLER_LIBS})
