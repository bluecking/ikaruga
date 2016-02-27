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

#include <vector>

using std::vector;

namespace jumper {

    class MainWindow;

    /**
     * @brief 	Represents a game instance.
     */
    class Game {
    public:

        /**
         * Constructor
         *
         * @param windows the main Window
         */
        Game(MainWindow *window);

        /// Destructor
        virtual ~Game();

        /**
         * sets the player
         *
         * @param player the player
         */
        void setPlayer(Player *player);

        /**
         * sets the level
         *
         * @param level the level
         */
        void setLevel(Level *level);

        /**
         * returns the current level
         *
         * @returns the level
         */
        Level *getLevel();

        /**
         * adds the actor to the game
         *
         * @param actor the actor to add
         */
        void addActor(Actor *actor);

        /**
         * Updates the current state according to the given key states
         *
         * @param currentKeyStates the current key states
         * @param keyDown if a key is pressed
         */
        void update(const Uint8 *&currentKeyStates, const bool *keyDown);

        /*
         * starts the game
         */
        void start();

        /*
         * sets the background layer
         *
         * @param layer the layer to set
         */
        void setLayer(TexturedLayer *layer) { m_layer = layer; };

        /*
         * sets the statusbar
         *
         * @param b the statusbar
         */
        void setStatusBar(StatusBar *b) { m_statusBar = b; };

    private:

        //moves the Actors
        void moveActors();

        //checks for player collisions
        void checkPlayerCollision();

        //checks for camera collisions
        void checkCameraCollision();

        /*
         * removes an Actor
         *
         * *param a the actor to remove
         */
        void removeActor(Actor *a);

        /**
         * Removes projectiles which are out of view.
         */
        void removeProjectiles();

        /**
         * Returns The time in seconds that has elapsed since the last frame.
         * @return The elapsed time.
         */
        float getElapsedTime();

        /**
         * Moves the player and camera for a given offset (m_scrollingSpeed)
         */
        void scrollHorizontal();

        //the start of the ticks
        float m_startTicks;

        /// All renderables in the game
        vector<Renderable *> m_renderables;

        /// All actors
        vector<Actor *> m_actors;

        /// The user controlled player
        Player *m_player;

        /// The current level
        Level *m_level;

        /// A Layer
        TexturedLayer *m_layer;

        /// A score board
        StatusBar *m_statusBar;

        /// Pointer to the main window of the game
        SDL_Renderer *m_renderer;

        /// Window width
        int m_windowWidth;

        /// Window height
        int m_windowHeight;

        bool m_started;

    };

} /* namespace jumper */

#endif /* SRC_GAME_HPP_ */
