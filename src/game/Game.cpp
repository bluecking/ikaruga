/*
 * Game.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: twiemann
 */

#include "Game.hpp"
#include "PuzzleBox.hpp"
#include "KillAnimation.hpp"

#include <iostream>
#include <algorithm>
#include <set>
using std::set;
using std::cout;
using std::endl;

namespace jumper
{

Game::Game(MainWindow* mainWindow)
{
	m_player = 0;
	m_level = 0;
	m_layer = 0;
	m_renderer = mainWindow->getRenderer();
	m_scoreBoard = 0;

	m_windowWidth = mainWindow->w();
	m_windowHeight = mainWindow->h();

	m_started = false;
    m_startTicks = 0;

	SDL_SetRenderDrawColor(m_renderer, 0, 102, 204, 255);
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

void Game::addActor(Actor* actor)
{
	m_actors.push_back(actor);
	m_renderables.push_back(actor);
}

void Game::update(const Uint8* &currentKeyStates)
{
	if(m_started)
	{
		// Reset forces and jump flags
        Vector2f moveForce(0.0, 0.0);

		if( currentKeyStates[ SDL_SCANCODE_UP ] )
		{
            moveForce.setY(-800.0);
		}
		if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
		{
            moveForce.setY(800.0);
		}
		if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
		{
            moveForce.setX(-800.0);
		}
		if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
		{
            moveForce.setX(800.0);
		}

        m_player->physics().setMoveForce(moveForce);

		moveActors();
		checkPlayerCollision();

		SDL_RenderClear(m_renderer);

		if(m_layer)
		{
			m_layer->render();
		}

		if(m_scoreBoard)
		{
			m_scoreBoard->setScore(m_player->physics().position().x());
			m_scoreBoard->render();
		}

		for(size_t i = 0; i < m_renderables.size(); i++)
		{
			m_renderables[i]->render();
		}

		updateCameraPosition();

        scrollHorizontal();

		// Update screen
		SDL_RenderPresent(m_renderer);
	}
}

void Game::removeActor(Actor* a)
{
	auto it = std::find(m_actors.begin(), m_actors.end(), a);
	m_actors.erase(it);

	auto it2 = std::find(m_renderables.begin(), m_renderables.end(), a);
	m_renderables.erase(it2);
}

void Game::checkPlayerCollision()
{
	set<Actor*> to_remove;
	KillAnimation* anim = 0;
	for(auto it = m_actors.begin(); it != m_actors.end(); it++)
	{
		Actor* a = *it;

		// Check for self collision
		if(a != m_player)
		{
			Collision c = m_player->getCollision(*a);

			// Simple items can be collected on the fly
			if(a->type() == ITEM && c.type() != NONE)
			{
				to_remove.insert(a);
			}

			// If an collection with an enemy occured, check
			// who killed whom (Player only can kill enemies
			// when falling down.
			if(a->type() == ENEMY  && c.type() != NONE)
			{
				if(c.type() == BOOM)
				{
					cout << "PLAYER KILLED" << endl;
				}
				else if(c.type() == DOWN)
				{
					to_remove.insert(a);
					anim = new KillAnimation(a);
				}
			}

			if(a->type() == PUZZLEBOX)
			{
				PuzzleBox* b = static_cast<PuzzleBox*>(a);
				m_player->resolveCollision(*a);
				if(c.type() == UP)
				{
					b->setHit(true);
				}
			}
		}
	}

	// Remove actors that were killed in this loop. We have to
	// store them separately because otherwise we would corrupt
	// to loop structure
	for(auto i = to_remove.begin(); i != to_remove.end(); i++)
	{
		removeActor(*i);
	}

	if(anim)
	{
		m_renderables.push_back(anim);
	}
}

void Game::moveActors()
{
	for(auto it = m_actors.begin(); it != m_actors.end(); it++)
	{
		(*it)->move(*m_level);
	}
}

void Game::start()
{
	m_started = true;
}

void Game::updateCameraPosition()
{
	/*if(m_player->position().x() > m_windowWidth / 2)
	{
		Vector2i position(m_player->position().x() - m_windowWidth / 2, 0);
		Renderable::m_camera.move(position);
	}*/


}

void Game::scrollHorizontal()
{
    float dt = getElapsedTime();

    if(dt > 0)
    {
        Vector2f scrollOffset(m_level->physics().getScrollingSpeed() * dt);
        m_player->setPosition(m_player->position() + scrollOffset);

        Renderable::m_camera.move(Renderable::m_camera.position() + scrollOffset);
    }
}

float Game::getElapsedTime()
{
    if(m_startTicks == 0)
    {
        m_startTicks = SDL_GetTicks();
    }

    Uint32 ticks = SDL_GetTicks();
    float time =  (ticks - m_startTicks) / 1000.0;
    m_startTicks = ticks;
    return time;
}

} /* namespace jumper */
