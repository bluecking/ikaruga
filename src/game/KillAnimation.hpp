/*
 * KillAnimation.hpp
 *
 *  Created on: Feb 21, 2016
 *      Author: twiemann
 */

#ifndef SRC_GAME_KILLANIMATION_HPP_
#define SRC_GAME_KILLANIMATION_HPP_

#include "Actor.hpp"

namespace jumper
{

class KillAnimation : public Actor
{
public:
	KillAnimation(Actor* actor ,std::string filepath);
	virtual ~KillAnimation();


	virtual void move(Level& level);
	//virtual void render();



	virtual void onTileCollision();

	virtual void onActorCollision(Actor& other);
};

} /* namespace jumper */

#endif /* SRC_GAME_KILLANIMATION_HPP_ */
