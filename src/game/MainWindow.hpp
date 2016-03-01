/*
 * MainWindow.hpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#ifndef SRC_MAINWINDOW_HPP_
#define SRC_MAINWINDOW_HPP_

#include <string>
#include <SDL.h>

#include "Game.hpp"
#include "WorldProperty.hpp"
#include "MainMenu.hpp"

namespace jumper
{
    class Game;
    class MainMenu;

    /**
     *	@brief Represents the main window of the game.
     */
    class MainWindow
    {
    public:

        /**
         * Creates a main window with given \ref title, width \ref w and height \ref h
         *
         * @param title		Title of the window
         * @param w			Width
         * @param h			Height
         */
        MainWindow(std::string title, int w, int h);

        /**
         * Destructor.
         */
        ~MainWindow();

        /**
         * Handles user events and renders the current level.
         */
        void run();

        /**
         * Gets the current SDL renderer
         */
        SDL_Renderer* getRenderer();

        void setGame(Game* game);

        void setMenu(MainMenu* menu);

        /// Returns the window width
        int w();

        /// Retruns the window height
        int h();

        ///Constants for setting the actual renderscreen
        static const int RENDER_MAINMENU=0;
        static const int RENDER_GAME=1;
        static const int RENDER_ITEMSHOP=2;
        static const int RENDER_CREDITS=3;

        ///Sets the Actual Render Screen
        void setActualScreen(int ID);

    private:

        /// Initializes all needed SDL resources
        void initSDL();

        /// Quits SDL and frees all resources
        void quitSDL();

        /**
         * Returns time used by the main loop in ms
         */
        float getLoopTime();

        /**
         * Limts the FPS by sleeping not used time
         */
        void limitFPS();

        /// SDL renderer struct
        SDL_Renderer* m_renderer;

        /// SDL main window struct
        SDL_Window* m_window;

        /// Window width
        int m_width;

        /// Window height
        int m_height;

        /// Window title
        std::string m_title;

        // Pointer to game
        Game* m_game;

        // Pointer to menu
        MainMenu* m_menu;

        // Timestamp from the start of the main loop
        Uint32 m_startLoopTicks;

        // Number of maximal fps
        static const int MAX_FPS;

        //Number for settings updatecall (actual Menu/Game)
        int actRenderID;
    };

} /* namespace jumper */

#endif /* SRC_MAINWINDOW_HPP_ */
