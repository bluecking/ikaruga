/*
 * KillAnimation.cpp
 *
 *  Created on: Feb 21, 2016
 *      Author: twiemann
 */

#include "KillAnimation.hpp"

#include <iostream>
using std::cout;
using std::endl;

namespace jumper
{

KillAnimation::KillAnimation(Actor* actor)
	: Item(actor->getRenderer(), actor->getTexture(), actor->frameWidth(), actor->frameHeight(), actor->numFrames())
{
	m_rotAngle = 0;
	m_yPos = actor->position().y();
	setPosition(actor->position());
	m_lastRenderTicks = 0;
}

void KillAnimation::render()
{
	Uint32 ticks = SDL_GetTicks();
	float time =  (ticks - m_lastRenderTicks);

	SDL_Rect dst;
	dst.w = w();
	dst.h = h();
	dst.x = floor(m_physicalProps.position().x()) - m_camera.x();
	dst.y = floor(m_yPos - m_camera.y());

	if(time > 10)
	{
		m_yPos+= 2;
		m_rotAngle++;

		// Save current tick count
		m_lastRenderTicks = ticks;
	}

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_RenderCopyEx(m_renderer, m_texture, &m_sourceRect, &dst, m_rotAngle, NULL, flip);

}

KillAnimation::~KillAnimation()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */
