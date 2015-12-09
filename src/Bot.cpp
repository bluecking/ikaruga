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
	: Actor(renderer, filename)
{
	m_physicalProps.setMoveForce(Vector2f(0,0));
}

Bot::~Bot()
{
	// TODO Auto-generated destructor stub
}

void Bot::move(Level& level)
{
	float dt = getElapsedTime();
	if(dt > 0)
	{
		Collision c = level.resolveCollision(this);

		//cout << c.delta() << endl;
		if(onGround() && c.delta().x() < 5)
		{
			physics().setMoveForce(800);
		}
		else if (onGround() && c.delta().x() > c.delta().y())
		{
			physics().setMoveForce(physics().moveForce() * -1);
		}


		Vector2f d_gravity;
		Vector2f d_move;

		d_gravity = level.physics().gravity() * dt;
		d_move = (physics().moveForce() * dt);

		// Update velocity
		physics().setVelocity(physics().velocity() + d_move + d_gravity);

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

		if(physics().velocity().y() > physics().maxFallVelocity() * dt)
		{
			physics().setVelocity(
					Vector2f(physics().velocity().x(), physics().maxFallVelocity() * dt));
		}



		// Set new player position
		physics().setPosition(physics().position() + physics().velocity());

	}

}

} /* namespace jumper */
