//
// Created by isaak on 26.11.15.
//


#include "Player.hpp"

#include <iostream>
using std::cout;
using std::endl;

namespace jumper
{

Player::Player(SDL_Renderer *renderer, std::string filename)
	: Actor(renderer, filename)
{

}

Player::Player(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
	: Actor(renderer, texture, frameWidth, frameHeight, numFrames)
{

}


void Player::move(Level& level)
{
	while(true)
	{
		m_camPosition = level.camPosition();
		nextFrame();
		float dt = getElapsedTime();
		if(dt > 0)
		{
			if(m_wantsToJump && onGround())
			{
				setJumping(true);
				m_wantsToJump = false;
			}

			Vector2f d_gravity;
			Vector2f d_move;

			d_gravity = level.physics().gravity() * dt;
			d_move = (physics().moveForce() * dt);

			// Update velocity
			physics().setVelocity(physics().velocity() + d_move + d_gravity);

			// Add jumping momentum
			if(jumping())
			{
				physics().velocity().setY(
						physics().velocity().y() + (physics().jumpForce().y() * dt) );
			}

			// Damp velocity according to extrinsic level damping
			physics().setVelocity(physics().velocity() * level.physics().damping());

			// Clamp velocities
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

			if(physics().velocity().y() < -physics().maxJumpVelocity() * dt)
			{
				physics().setVelocity(
						Vector2f(physics().velocity().x(), -physics().maxJumpVelocity() * dt));
			}

			// Set new player position
			physics().setPosition(physics().position() + physics().velocity());

			/*	// Move camera if player position exceeds window with / 2
		m_camera.position().setX(position().x() - m_levelWidth / 2 + w());
		if(m_camera.position().x() < 0)
		{
			m_camera.position().setX(0);
		}*/

			// Stop jumping at maximum jumping height
			if(fabs(physics().position().y() - jumpStart()) >= physics().maxJumpHeight())
			{
				setJumping(false);
			}

			Collision c = level.resolveCollision(this);
			//cout << c.delta() << endl;
		}
	}
}

}
