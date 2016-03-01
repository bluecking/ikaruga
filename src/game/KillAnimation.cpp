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
	: Item(actor->getRenderer(),
		   actor->getTexture(),
		   actor->frameWidth(),
		   actor->frameHeight(),
		   actor->numFrames(),
 		   actor->getHealth(),
		   actor->getCollisionDamage())
{
	m_rotAngle = 0;
	m_yPos = actor->position().y();
	setPosition(actor->position());
	m_lastRenderTicks = 0;
	m_texture = actor->getTexture();
	m_numFrames = 2;
	m_currentFrame = 0;
	m_texture = TextureFactory::instance(m_renderer).getTexture("/home/marius/git/CPPP/praktikum1/res/images/explosions.png");
}
/*
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
*/

void KillAnimation::move(Level& level)
	{

		Uint32 ticks = SDL_GetTicks();
		float time = (ticks - m_lastRenderTicks);
		cout<<this->m_currentFrame<<endl;

		if (time > m_frameTimeout)
		{
			// Check and increase frame counter
			if (this->m_currentFrame + 1 < this->m_numFrames)
			{
				this->m_currentFrame++;
			}
			else
			{
				this->m_currentFrame = 0;
			}

			// Render next tile row
			m_currentTileRow = m_nextTileRow;

			// Setup source rect
			m_sourceRect.x = m_currentFrame * m_frameWidth;
			m_sourceRect.y = m_currentTileRow * m_frameHeight;

			// Save current tick count
			m_lastRenderTicks = ticks;
		}
		cout<<this->m_currentFrame<<endl;
	}

KillAnimation::~KillAnimation()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */
