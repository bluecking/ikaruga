/*
 * KillAnimation.cpp
 *
 *  Created on: Feb 21, 2016
 *      Author: twiemann
 */

#include "KillAnimation.hpp"



using std::cout;
using std::endl;

namespace jumper
{

KillAnimation::KillAnimation(Actor* actor, std::string filepath)
	: Item(actor->getRenderer(),
		   actor->getTexture(),
		   40,
		   40,
		   4,
 		   4,
		   actor->getCollisionDamage())
{

	setPosition(actor->position());
	m_lastRenderTicks = 0;
	m_currentFrame = 0;
	m_texture = TextureFactory::instance(m_renderer).getTexture(filepath);
	m_type = ITEM;
	setFPS(8);
    m_color = actor->getColor();
    m_colorOffset = actor->getColorOffset();
}

void KillAnimation::move(Level& level)
	{
        nextFrame();
        //this will kill the animation once it has played fully
		if(m_currentFrame == m_numFrames -1)
		{
			m_health = 0;
		}
	}

KillAnimation::~KillAnimation()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */
