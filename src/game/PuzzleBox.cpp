/*
 * PuzzleBox.cpp
 *
 *  Created on: Feb 21, 2016
 *      Author: twiemann
 */

#include "PuzzleBox.hpp"

namespace jumper
{

PuzzleBox::PuzzleBox(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
	: Item(renderer, texture, frameWidth, frameHeight, numFrames, 100, 0), m_hit(false)
{
	m_hitRect.x = numFrames * frameWidth;
	m_hitRect.y = 0;
	m_hitRect.w = frameWidth;
	m_hitRect.h = frameHeight;
}

void PuzzleBox::render()
{
	if(!m_hit)
	{
		Item::render();
	}
	else
	{
		SDL_Rect target;

		target.x = floor(m_physicalProps.position().x()) - m_camera.x();
		target.y = floor(m_physicalProps.position().y()) - m_camera.y();
		target.w = m_frameWidth;
		target.h = m_frameHeight;

		SDL_RenderCopy(m_renderer, m_texture, &m_hitRect, &target);
	}
}

PuzzleBox::~PuzzleBox()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */
