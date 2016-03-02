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
#include "LaserWeapon.hpp"
#include "PowerUpHeal.hpp"
#include "../xml/XML.hpp"
//#include "Main.cpp"

#include <vector>
#include "FontRender.hpp"

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


        void setSound(std::string soundFile, int volume);

        Vector2f getPlayerPosition();

        void setSound(std::string soundFile);

        static const int PIXELS_OFFSET_SPAWN_BOTS = 40;
        static const int PIXELS_OFFSET_RENDER = 40;

        static void setupGame(string filename, MainWindow* w, Game* game);

        static void setupBots(vector<XML::LevelBot> bots, MainWindow* w, Game* game, std::string filepath);

        static void setupItems(vector<XML::LevelItem> items, MainWindow* w, Game* game, std::string filepath);

        static void setupPlayer(XML::Player xplayer, MainWindow* w, Game* game, std::string filepath);

        static void setupStatusbar(MainWindow* w, Game* game, XML::Statusbar statusbar, std::string filepath);

        static void setupBackground(XML::Background background, std::string filepath, MainWindow* w, Game* game);

        static void setupLevel(MainWindow* w, Game* game, std::string filepath);

        static void getBotProperty(XML::LevelBot bot, PlayerProperty& p);

        static void getPlayerProperty(XML::Player player, PlayerProperty& p);

        void setBossFight(bool bossfight);

        void bossFight();

        bool getBossFight();

        void setBossFightAt(int bossFightAt);

        int getBossFightAt();

        void setActorOptionsOnKill(Actor* actor);

        void setBossHealth(int health);

        void end();

        Actor* getLastBoss();


    protected:
        bool m_bossFight;

    private:

        void printStartScreen();

        void printEndScreen();

        int m_boss_health;

        int m_bossFightAt;

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

        int m_volume;

        /**
         * Is invoked by Game::updaL m_xml;te() and checks if an Actor collides with another Actor.
         */
        void checkActorCollision();

        /**
         * Is invoked by Game::update() and remove Actors with health below 0.
         */
        void removeDeadActors();
        vector<Bot*> m_bots;

        Sound m_sound;

        string m_explosionAnimation;

    };

} /* namespace jumper */

#endif /* SRC_GAME_HPP_ */
