# Setup sources
set(JUMPER_SOURCES
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
        ScoreBoard.cpp
        SparseMatrix.cpp
        SparseVector.cpp
        StaticRenderable.cpp
        TextureFactory.cpp
        TexturedLayer.cpp
        WorldProperty.cpp
        Weapon.cpp
        Projectile.cpp
        LaserWeapon.cpp
        Armed.cpp CollisionManager.cpp CollisionManager.hpp)

set(JUMPER_LIBS ${JUMPER_LIBS} xml)

# Build executable
add_executable(jumper ${JUMPER_SOURCES})
target_link_libraries(jumper ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY})
target_link_libraries(jumper m)
target_link_libraries(jumper ${Boost_LIBRARIES})
target_link_libraries(jumper ${JUMPER_LIBS})
