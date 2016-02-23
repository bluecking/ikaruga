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

   //TODO: THIS FOR TESTING AND NEEDS TO BE PARAMETER
    m_health=10000;
}

Bot::Bot(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
  	: Actor(renderer, texture, frameWidth, frameHeight, numFrames)
{
	m_physicalProps.setMoveForce(Vector2f(0,0));
	m_physicalProps.setMaxRunVelocity(50);

    //TODO: THIS FOR TESTING AND NEEDS TO BE PARAMETER
    m_health=10000;
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
        Vector2f d_move(80.0,12.0);
        physics().setPosition(physics().position() + d_move*dt);

	};
}



} /* namespace jumper */
