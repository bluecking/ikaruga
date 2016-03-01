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
	KillAnimation(Actor* actor ,std::string filepath);
	virtual ~KillAnimation();


	virtual void move(Level& level);
	//virtual void render();



};

} /* namespace jumper */

#endif /* SRC_GAME_KILLANIMATION_HPP_ */
