/*
 * MainWindow.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "MainWindow.hpp"
#include "Pixel.hpp"

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
	m_renderTime = 0;
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
	const Uint8* currentKeyStates;
	Pixel offset;
	int moveX;
	int moveY;
	bool jump;
	// Start main loop and event handling
	while(!quit && m_renderer)
	{
		m_startTicks = SDL_GetTicks();
		offset.setX(0);
		offset.setY(0);
		moveX = 0;
		moveY = 0;
		jump = false;
		// Process events, detect quit signal for window closing
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		currentKeyStates = SDL_GetKeyboardState( NULL );

		if( currentKeyStates[ SDL_SCANCODE_UP ] )
		{
			moveY = -1;
		}
		if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
		{
			moveY = 1;
		}
		if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
		{
			moveX = -1;
		}
		if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
		{
			moveX = 1;
		}
		if( currentKeyStates[ SDL_SCANCODE_SPACE ])
		{
			jump = true;
			//std::cout << "jump!" << std::endl;
		}
		//m_camera.move(offset);
		updatePlayerPosition(moveX, jump, m_renderTime);
		checkAndResolveCollision();

		// Clear screen
		SDL_RenderClear(m_renderer);

		// Render Level
		if(m_level)
		{
			m_level->render();
		}
		m_player->render();
		//SDL_Delay(10);

		// Update screen
		SDL_RenderPresent(m_renderer);
		m_renderTime = (SDL_GetTicks() - m_startTicks) / 1000.0;
	}

}

Camera & MainWindow::getCam()
{
	return m_camera;
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

void MainWindow::setPlayer(Player* player)
{
	m_player = player;
}

void MainWindow::checkAndResolveCollision()
{
	SDL_Rect tileRect;
	SDL_Rect spriteRect;
	SDL_Rect intersectionRect;
	Vector2f desiredPosition;
	Vector2I surroundingTiles[8];
	int n, i ,j;

	/* Convert the player sprite's screen position to global position */
	Vector2f global_pos = m_player->position() + Vector2f(m_camera.position().x(), m_camera.position().y());

	/* Set desired position to new position */
	desiredPosition = global_pos;


	/* Check if sprite intersects with one of its surrounding tiles */
	m_level->surroundingTiles(global_pos, m_player->w(), m_player->h(), m_camera, surroundingTiles);
	int d_i, d_j;
	int f_i, f_j;
	m_player->setOnGround(false);
	f_i = surroundingTiles[6].y();
	f_j = surroundingTiles[6].x();

	if(m_player->physics().velocity().x() > 0)
	{
		d_i = surroundingTiles[7].y();
		d_j = surroundingTiles[7].x();
	}
	else
	{
		d_i = surroundingTiles[5].y();
		d_j = surroundingTiles[5].x();
	}

	if(f_i < m_level->levelHeight() && f_j < m_level->levelWidth())
	{
		if(m_level->tiles()[f_i][f_j] > 0) m_player->setOnGround(true);
	}


	if(d_i < m_level->levelHeight() && d_j < m_level->levelWidth() )
	{
		if(m_level->tiles()[d_i][d_j] > 0) m_player->setOnGround(true);
	}


	for(n = 0; n < 8; n++)
	{
		j = surroundingTiles[n].x();
		i = surroundingTiles[n].y();

		/* Check, if tile coordinates are valid */
		if((i >= 0) && (i < m_level->levelHeight()) && (j >= 0) && (j < m_level->levelWidth()) )
		{


			if(m_level->tiles()[i][j] > 0)
			{

				/* Get SDL rect for current tile and sprite and check intersection */
				tileRect.y = i * m_level->tileHeight();
				tileRect.x = j * m_level->tileWidth();
				tileRect.w = m_level->tileWidth();
				tileRect.h = m_level->tileHeight();

				spriteRect.x = desiredPosition.x();
				spriteRect.y = desiredPosition.y();
				spriteRect.w = m_player->w();
				spriteRect.h = m_player->h();

				if(SDL_IntersectRect(&tileRect, &spriteRect, &intersectionRect))
				{



					if(n == 6)
					{
						m_player->setOnGround(true);
					}

					/* Handle pose correction cases */
					if(n == 4)
					{
						desiredPosition.setX(desiredPosition.x() - intersectionRect.w);
					}
					else if(n == 1)
					{
						desiredPosition.setY(desiredPosition.y() + intersectionRect.h);
						m_player->setJumping(false);
					}
					else if(n == 3)
					{
						desiredPosition.setX(desiredPosition.x() + intersectionRect.w);
					}
					else if(n == 6)
					{
						desiredPosition.setY(desiredPosition.y() - intersectionRect.h);
					}
					else
					{
						if(intersectionRect.w >= 2 && intersectionRect.h >= 2)
						{
							if(intersectionRect.w > intersectionRect.h)
							{
								if( (n == 5) || (n == 7))
								{
									desiredPosition.setY(desiredPosition.y() - intersectionRect.h);
								}
								else
								{
									desiredPosition.setY(desiredPosition.y() + intersectionRect.h);
								}
							}
							else
							{
								if( (n == 2) || (n == 7))
								{
									desiredPosition.setX(desiredPosition.x() - intersectionRect.w);
								}
								else
								{
									desiredPosition.setX(desiredPosition.x() + intersectionRect.w);
								}
								if( (n == 0) || (n == 2) )
								{
									m_player->setJumping(false);
								}
							}
						}
					}
				}
			}
		}
	}

	m_player->setPosition(Vector2f(desiredPosition.x() - m_camera.position().x(), desiredPosition.y() - m_camera.position().y()));


}

void MainWindow::updatePlayerPosition(int move, bool jump, double dt)
{
	m_player->animate();
	if(dt > 0)
	{

		if(dt > 0 && jump && m_player->onGround())
		{
			m_player->setJumping(true);
		}

		Vector2f d_gravity;
		Vector2f d_move;

		d_gravity = m_level->getPhysics().gravity() * dt;

		if(move != 0)
		{
			d_move = (m_level->getPhysics().move() * dt) * move;
		}
		else
		{
			d_move.setX(0);
			d_move.setY(0);
		}

		// Update velocity
		m_player->physics().setVelocity(m_player->physics().velocity() + d_move + d_gravity);

		// Add jumping momentum
		if(m_player->jumping())
		{
			m_player->physics().velocity().setY(
					m_player->physics().velocity().y() + (m_level->getPhysics().jumpForce().y() * dt) );
		}

		// Damp velocity according to extrinsic level damping
		m_player->physics().setVelocity(m_player->physics().velocity() * m_level->getPhysics().damping());

		// Clamp velocities
		if(m_player->physics().velocity().x() > m_level->getPhysics().maxVelocity() * dt)
		{
			m_player->physics().setVelocity(Vector2f(m_level->getPhysics().maxVelocity() * dt,
													 m_player->physics().velocity().y()));
		}

		if(m_player->physics().velocity().x() < -m_level->getPhysics().maxVelocity() * dt)
		{
			m_player->physics().setVelocity(Vector2f(-m_level->getPhysics().maxVelocity() * dt,
													 m_player->physics().velocity().y()));
		}

		if(m_player->physics().velocity().y() > m_level->getPhysics().maxFallVelocity() * dt)
		{
			m_player->physics().setVelocity(
					Vector2f(m_player->physics().velocity().x(), m_level->getPhysics().maxFallVelocity() * dt));
		}

		if(m_player->physics().velocity().y() < -m_level->getPhysics().maxJumpVelocity() * dt)
		{
			m_player->physics().setVelocity(
					Vector2f(m_player->physics().velocity().x(), -m_level->getPhysics().maxJumpVelocity() * dt));
		}

		// Set new player position
		m_player->physics().setPosition(m_player->physics().position() + m_player->physics().velocity());


		// Move camera if player position exceeds window with / 2
		m_camera.position().setX(m_player->position().x() - m_width / 2 + m_player->w());
		if(m_camera.position().x() < 0)
		{
			m_camera.position().setX(0);
		}

		// Stop jumping at maximum jumping height
		if(fabs(m_player->physics().position().y() - m_player->jumpStart()) >= m_level->getPhysics().jumpHeight())
		{
			m_player->setJumping(false);
		}


		//std::cout << m_camera.position() << std::endl;
		//std::cout << m_camera.position() << std::endl;
	}
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
