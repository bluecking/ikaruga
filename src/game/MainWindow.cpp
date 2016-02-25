/*
 * MainWindow.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "MainWindow.hpp"
#include <SDL_image.h>
#include <iostream>
#include "Vector.hpp"
#include "Renderable.hpp"

namespace jumper
{


    MainWindow::MainWindow(std::string title, int w, int h)
    {
        /// Init width and height
        m_width = w;
        m_height = h;

        /// Set pointer to NULL
        m_renderer = 0;

        /// Init the camera for all renderables
        Renderable::m_camera.m_width = w;
        Renderable::m_camera.m_height = h;
        /// Initialize SDL stuff
        initSDL();
    }

    MainWindow::~MainWindow()
    {
        quitSDL();
    }

    SDL_Renderer* MainWindow::getRenderer()
    {
        return m_renderer;
    }

    void MainWindow::run()
    {
        bool quit = false;
        SDL_Event e;
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        bool* keyDown = new bool[SDL_NUM_SCANCODES];

        // Start main loop and event handling
        while (!quit && m_renderer)
        {
            // Process events, detect quit signal for window closing
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }

                // collect down keys
                if (e.key.type == SDL_KEYDOWN && e.key.repeat == 0)
                {
                    keyDown[e.key.keysym.scancode] = true;
                }
            }

            m_game->update(currentKeyStates, keyDown);

            // reset key down
            for (int i = 0; i < SDL_NUM_SCANCODES; i++)
            {
                keyDown[i] = false;
            }

            SDL_Delay(16);
        }
    }

    void MainWindow::setGame(Game* game)
    {
        m_game = game;
    }

    void MainWindow::initSDL()
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "SDL could not initialize: " << SDL_GetError() << std::endl;
            return;
        }

        // Generate SDL main window
        m_window = SDL_CreateWindow(
                "Jumper Main Window",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                m_width,
                m_height,
                SDL_WINDOW_SHOWN);

        if (m_window == NULL)
        {
            std::cout << "SDL window could not be generated: " << SDL_GetError() << std::endl;
        }
        else
        {

            // Create renderer for the SDL main window
            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

            if (m_renderer == NULL)
            {
                std::cout << "SDL could not generate renderer: " << SDL_GetError() << std::endl;
            }
            else
            {
                // Set background color for renderer
                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0);
            }
        }

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        }
    }


    void MainWindow::quitSDL()
    {
        // Destroy window and renderer
        if (m_window)
        {
            SDL_DestroyWindow(m_window);
            m_window = 0;
        }

        if (m_renderer)
        {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = 0;
        }

        // Quit SDL and SDL_Image
        IMG_Quit();
        SDL_Quit();
    }

    int jumper::MainWindow::w()
    {
        return m_width;
    }

    int jumper::MainWindow::h()
    {
        return m_height;
    }

} /* namespace jumper */


