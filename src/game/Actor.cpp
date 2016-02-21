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
	m_focus = false;
	m_jumpStart = 0;
	m_physicalProps.setPosition(Vector2f(100, 0));
	m_startTicks = 0;
	m_numFrames = 1;
	m_type = ACTOR;
}

Actor::Actor(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
	: AnimatedRenderable(renderer, texture, frameWidth, frameHeight, numFrames)
{
	m_jumping = 0;
	m_wantsToJump = false;
	m_onGround = false;
	m_focus = false;
	m_jumpStart = 0;
	m_physicalProps.setPosition(Vector2f(100, 0));
	m_startTicks = 0;
	m_type = ACTOR;
}

void Actor::setPhysics(PlayerProperty p)
{
	m_physicalProps = p;
}

Actor::~Actor()
{

}

void Actor::wantsToJump(bool j)
{
	m_wantsToJump = j;
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

    target.x = floor(m_physicalProps.position().x()) - m_camera.x();
    target.y = floor(m_physicalProps.position().y()) - m_camera.y();
    target.w = m_frameWidth;
    target.h = m_frameHeight;

    // Do not render if actor is outside frustrum
    if(target.x + target.h > 0 && target.x + target.h < m_camera.w())
    {
    	SDL_RendererFlip flip;
    	if(m_physicalProps.velocity().x() > 0)
    	{
    		flip = SDL_FLIP_HORIZONTAL;
    	}
    	else
    	{
    		flip = SDL_FLIP_NONE;
    	}

    	// Render current animation frame
    	SDL_RenderCopyEx( getRenderer(), m_texture, &m_sourceRect, &target, 0, NULL, flip);
    }

}

void Actor::setPosition(Vector2f pos)
{
    m_physicalProps.position() = pos;
}

bool Actor::onGround() const
{
    return m_onGround;
}

void Actor::setOnGround(bool onGround)
{
    m_onGround = onGround;
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

Collision Actor::getCollision(Actor& other)
{
	Collision c;

	// Check for collision
	Vector2f v = m_physicalProps.velocity();

	SDL_Rect myRect;
	myRect.x = position().x();
	myRect.y = position().y();
	myRect.w = w();
	myRect.h = h();

	SDL_Rect otherRect;
	otherRect.x = other.position().x();
	otherRect.y = other.position().y();
	otherRect.w = other.w();
	otherRect.h = other.h();

	SDL_Rect intersection;
	SDL_IntersectRect(&myRect, &otherRect, &intersection);

	if(intersection.w > 0 && intersection.h > 0)
	{
		if(v.y() > 0)
		{
			if(intersection.h < otherRect.h / 2)
			{
				c.setType(DOWN);
			}
			else
			{
				c.setType(BOOM);
			}
		}
		else
		{
			if(intersection.h < otherRect.h / 2)
			{
				c.setType(UP);
			}
			else
			{
				c.setType(BOOM);
			}
		}
	}

	return c;
}

void jumper::Actor::setFocus(bool focus)
{
	m_focus = focus;
}

bool jumper::Actor::hasFocus()
{
	return m_focus;
}


} /* namespace jumper */

