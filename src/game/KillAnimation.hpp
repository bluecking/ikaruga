/*
 * KillAnimation.hpp
 *
 *  Created on: Feb 21, 2016
 *      Author: twiemann
 */

#ifndef SRC_GAME_KILLANIMATION_HPP_
#define SRC_GAME_KILLANIMATION_HPP_

#include "Item.hpp"

namespace jumper
{

class KillAnimation : public Item
{
public:
	KillAnimation(Actor* actor);
	virtual ~KillAnimation();

	virtual void render();

private:
	float 		m_rotAngle;
	int			m_yPos;

};

} /* namespace jumper */

#endif /* SRC_GAME_KILLANIMATION_HPP_ */
