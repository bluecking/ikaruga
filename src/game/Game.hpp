/*
 * Game.hpp
 *
 *  Created on: Dec 11, 2015
 *      Author: twiemann
 */

#ifndef SRC_GAME_HPP_
#define SRC_GAME_HPP_

#include "MainWindow.hpp"
#include "Actor.hpp"
#include "Bot.hpp"
#include "Player.hpp"
#include "Level.hpp"
#include "TexturedLayer.hpp"
#include "StatusBar.hpp"
#include "Collidable.hpp"
#include "StatusBar.hpp"
#include "Sound.hpp"
#include "Vector.hpp"

#include "../xml/XML.hpp"

#include <vector>

using std::vector;

namespace jumper
{
    class Bot;
    class MainWindow;

/**
 * @brief 	Represents a game instance.
 */
    class Game
    {
    public:

        /// Constructor
        Game(MainWindow* window);

        /// Destructor
        virtual ~Game();

        /// Sets the player object
        void setPlayer(Player* player);

        /// Sets the current level
        void setLevel(Level* level);

        /// Gets the current Level
        Level* getLevel();

        /// Adds a new bot to the scene
        void addActor(Actor* actor);

        /// Updates the current state according to the given key states
        void update(const Uint8*& currentKeyStates, const bool* keyDown);

        /// Starts the game
        void start();

        /// Sets a layer for background rendering
        void setLayer(TexturedLayer* layer)
        { m_layer = layer; };

        /// Adds a score board
        void setStatusBar(StatusBar * b)
        { m_statusBar = b; };

        /// set bots
        void addBot(Bot* bot);

        Vector2f getPlayerPosition();

        void setSound(std::string soundFile);

        static const int PIXELS_OFFSET_SPAWN_BOTS = 40;
        static const int PIXELS_OFFSET_RENDER = 40;

    private:


        void moveActors();

        void checkCameraCollision();

        void removeActor(Actor* a);

        /**
         * Returns The time in seconds that has elapsed since the last frame.
         * @return The elapsed time.
         */
        float getElapsedTime();

        /**
         * Moves the player and camera for a given offset (m_scrollingSpeed)
         */
        void scrollHorizontal();

        void spawnBots();

        float m_startTicks;

        /// All renderables in the game
        vector<Renderable*> m_renderables;

        /// All actors
        vector<Actor*> m_actors;

        /// The user controlled player
        Player* m_player;

        /// The current level
        Level* m_level;

        /// A Layer
        TexturedLayer* m_layer;

        /// A score board
        StatusBar * m_statusBar;

        /// Pointer to the main window of the game
        SDL_Renderer* m_renderer;

        /// Window width
        int m_windowWidth;

        /// Window height
        int m_windowHeight;

        bool m_started;

        /**
         * Is invoked by Game::update() and checks if an Actor collides with another Actor.
         */
        void checkActorCollision();

        /**
         * Is invoked by Game::update() and remove Actors with health below 0.
         */
        void removeDeadActors();
        vector<Bot*> m_bots;

        Sound m_sound;

    };

} /* namespace jumper */

#endif /* SRC_GAME_HPP_ */
