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
        CollisionManager.cpp
        CollisionManager.hpp
        Armed.cpp
        StatusBar.cpp
        FontRender.cpp
        Sound.cpp
        Filesystem.cpp
        PowerUp.cpp
        PowerUpHeal.cpp
        ItemShop.cpp
        HighScore.cpp
        Filesystem.cpp
        Profile.cpp
        MainMenu.cpp
        PowerUpGodMode.cpp)

set(JUMPER_LIBS ${JUMPER_LIBS}
        xml
        ${Boost_LIBRARIES}
        ${SDL2_LIBRARY}
        ${SDL2_IMG_LIBRARY}
        ${SDL2_MIXER_LIBRARY})

# Build executable
add_executable(jumper ${JUMPER_SOURCES})
target_link_libraries(jumper ${JUMPER_LIBS})
