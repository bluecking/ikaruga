/*
 * Actor.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#include <SDL.h>

#include <iostream>
using std::cout;
using std::endl;

#include "Actor.hpp"

namespace jumper
{

Actor::Actor(SDL_Renderer* renderer, std::string filename)
	: AnimatedRenderable(renderer, filename)
{
	m_jumping = 0;
	m_wantsToJump = false;
	m_onGround = false;
	m_jumpStart = 0;
	m_physicalProps.setPosition(Vector2f(100, 0));
	m_startTicks = 0;
}

Actor::~Actor()
{
	// TODO Auto-generated destructor stub
}

void Actor::jump()
{
	m_wantsToJump = false;
}

float Actor::getElapsedTime()
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

void Actor::render()
{
    SDL_Rect target;
    SDL_RendererFlip flip;
    if(m_physicalProps.velocity().x() > 0)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else
    {
        flip = SDL_FLIP_NONE;
    }

    target.x = m_physicalProps.position().x();
    target.y = m_physicalProps.position().y();
    target.w = m_frameWidth;
    target.h = m_frameHeight;

    cout << target.x << " " << target.y << endl;

    /* Render current animation frame */
    SDL_RenderCopyEx( getRenderer(), m_texture, &m_sourceRect, &target, 0, NULL, flip);
}

void Actor::setPosition(Vector2f pos)
{
    m_physicalProps.position() = pos;
}

bool Actor::onGround() const
{
    return m_onGround;
}

void Actor::setOnGround(bool m_onGround)
{
    m_onGround = m_onGround;
}

PlayerProperty& Actor::physics()
{
    return m_physicalProps;
}

bool Actor::jumping()
{
    return m_jumping;
}

void Actor::setJumping(bool jump)
{
    if(jump) m_jumpStart = m_physicalProps.position().y();
    m_jumping = jump;
}

int Actor::jumpStart()
{
    return m_jumpStart;
}

Vector2f Actor:: position()
{
	return m_physicalProps.position();
}

void Actor::getCollision(Actor& other)
{

}

void Actor::getCollision(Level& other)
{

}

} /* namespace jumper */
