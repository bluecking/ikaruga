/*
 * Bot.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#include "Bot.hpp"

#include <iostream>
using std::cout;
using std::endl;

namespace jumper
{

Bot::Bot(SDL_Renderer* renderer, std::string filename)
	: Actor(renderer, filename), m_bouncePos(0)
{
	m_physicalProps.setMoveForce(Vector2f(0,0));
	m_physicalProps.setMaxRunVelocity(50);
}

Bot::Bot(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
  	: Actor(renderer, texture, frameWidth, frameHeight, numFrames)
{
	m_physicalProps.setMoveForce(Vector2f(0,0));
	m_physicalProps.setMaxRunVelocity(50);
}

Bot::~Bot()
{
	// TODO Auto-generated destructor stub
}

void Bot::move(Level& level)
{
	nextFrame();
	float dt = getElapsedTime();
	if(dt > 0)
	{
		Collision c = level.resolveCollision(this);
		if(c.delta().x() > 5)
		{
			bounce();
		}

		if(fabs(physics().moveForce().x()) < 2)
		{
		physics().setMoveForce(Vector2f(100, 0));
		}

		Vector2f d_move;

		d_move = (physics().moveForce() * dt);

		// Update velocity
		physics().setVelocity(physics().velocity() + d_move);

		// Damp velocity according to extrinsic level damping
		physics().setVelocity(physics().velocity() * level.physics().damping());

		if(physics().velocity().x() > physics().maxRunVelocity() * dt)
		{
			physics().setVelocity(Vector2f(physics().maxRunVelocity() * dt,
					physics().velocity().y()));
		}

		if(physics().velocity().x() < -physics().maxRunVelocity() * dt)
		{
			physics().setVelocity(Vector2f(-physics().maxRunVelocity() * dt,
					physics().velocity().y()));
		}

		// Set new player position
		physics().setPosition(physics().position() + physics().velocity());

	}
}

void Bot::bounce()
{
	if(fabs(physics().position().x() - m_bouncePos.x()) > 5)
	{
		physics().setMoveForce(physics().moveForce() * -1);
		m_bouncePos = physics().position();
	}
}

} /* namespace jumper */
