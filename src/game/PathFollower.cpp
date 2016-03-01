/*
 * AutoPlayer.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: twiemann
 */

#include "PathFollower.hpp"

#include <iostream>
using std::cout;
using std::endl;
namespace jumper
{

PathFollower::PathFollower(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
	: Actor(renderer, texture, frameWidth, frameHeight, numFrames, 100, 0)
{

}

void PathFollower::render()
{
	SDL_Rect target;

	target.x = floor(m_physicalProps.position().x()) - m_camera.x() - m_sourceRect.w / 2;
	target.y = floor(m_physicalProps.position().y()) - m_camera.y() - m_sourceRect.h / 2;
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

void PathFollower::move(Level& l)
{
	if(m_path.size() >= 2)
	{
		// Get iterator for current node
		std::list<Vector2f>:: iterator current = m_path.begin();
		std::list<Vector2f>:: iterator next = m_path.begin()++;

		Vector2f incl = getNormalDirection(next, current);
		m_physicalProps.setPosition(*current);

		if(next != m_path.end())
		{
			nextFrame();
			if(m_physicalProps.position().distanceTo(*next) < 3)
			{
				// Update target position
				current = next;
				next++;

				// Update inclination
				incl = 	getNormalDirection(next, current);

				// Clamp sprite to next node position
				m_physicalProps.setPosition(*current);

				// Set dummy velocity for correct flipping when rendering
				// the sprite
				m_physicalProps.velocity().setX(incl.x());
			}
			m_physicalProps.setPosition(m_physicalProps.position() + incl );
		}
	}
}

Vector2f PathFollower:: getNormalDirection(std::list<Vector2f>::iterator s, std::list<Vector2f>::iterator e)
{
	// Update inclination
	float x_diff = s->x() - e->x();
	float y_diff = s->y() - e->y();
	float length = sqrt(x_diff * x_diff + y_diff * y_diff);
	return Vector2f(x_diff / length, y_diff / length);
}

PathFollower::~PathFollower()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */
