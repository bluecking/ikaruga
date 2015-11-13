/*
 * MainWindow.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "MainWindow.hpp"

#include <SDL_image.h>
#include <iostream>

namespace jumper
{


MainWindow::MainWindow(std::string title, int w, int h)
{
	/// Init width and height
	m_width = w;
	m_height = h;

	/// Set pointer to NULL
	m_renderer = 0;
	m_level = 0;

	/// Initialize SDL stuff
	initSDL();
}

MainWindow::~MainWindow()
{
	quitSDL();
}

void MainWindow::run()
{
	bool quit = false;
	SDL_Event e;

	// Start main loop and event handling
	while(!quit && m_renderer)
	{
		// Process events, detect quit signal for window closing
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// Clear screen
		SDL_RenderClear(m_renderer);

		// Render Level
		if(m_level)
		{
			m_level->render();
		}

		// Update screen
		SDL_RenderPresent(m_renderer);
	}

}

SDL_Renderer* MainWindow::getRenderer()
{
	return m_renderer;
}

void MainWindow::initSDL()
{
	// Initialize SDL
	if(SDL_Init( SDL_INIT_VIDEO ) < 0)
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
				SDL_WINDOW_SHOWN );

	if(m_window == NULL)
	{
		std::cout << "SDL window could not be generated: " << SDL_GetError() << std::endl;
	}
	else
	{

		// Create renderer for the SDL main window
		m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );

		if(m_renderer == NULL)
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
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
	}
}

void MainWindow::setLevel(Level* level)
{
	m_level = level;
}

void MainWindow::quitSDL()
{
	// Destroy window and renderer
	if(m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = 0;
	}

	if(m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = 0;
	}

	// Quit SDL and SDL_Image
	IMG_Quit();
	SDL_Quit();
}

} /* namespace jumper */
