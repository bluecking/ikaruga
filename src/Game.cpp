/*
 * Game.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: twiemann
 */

#include "Game.hpp"

namespace jumper
{

Game::Game(MainWindow* mainWindow)
{
	m_player = 0;
	m_level = 0;
	m_renderer = mainWindow->getRenderer();
}

Game::~Game()
{
	// TODO Auto-generated destructor stub
}

void Game::setPlayer(Player* player)
{
	m_player = player;
	m_actors.push_back(player);
	m_renderables.push_back(player);
}

void Game::setLevel(Level* level)
{
	m_level = level;
	m_renderables.push_back(level);
}

void Game::addBot(Bot* bot)
{
	m_actors.push_back(bot);
	m_renderables.push_back(bot);
}

void Game::update(const Uint8* &currentKeyStates)
{
	// Reset forces and jump flags
	m_player->physics().setMoveForce(Vector2f(0.0, 0.0));
	m_player->wantsToJump(false);

	if( currentKeyStates[ SDL_SCANCODE_UP ] )
	{

	}
	if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
	{

	}
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
	{
		m_player->physics().setMoveForce(Vector2f(-800.0, 0.0));

	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		m_player->physics().setMoveForce(Vector2f(800.0, 0.0));
	}
	if( currentKeyStates[ SDL_SCANCODE_SPACE ])
	{
		m_player->wantsToJump(true);
	}

	for(size_t i = 0; i < m_actors.size(); i++)
	{
		m_actors[i]->move(*m_level);
	}

	SDL_RenderClear(m_renderer);
	for(size_t i = 0; i < m_renderables.size(); i++)
	{
		m_renderables[i]->render();
	}

	// Update screen
	SDL_RenderPresent(m_renderer);

}

} /* namespace jumper */