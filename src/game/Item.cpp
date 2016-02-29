/*
 * Item.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: twiemann
 */

#include "Item.hpp"

namespace jumper
{
Item::Item(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth,
		int frameHeight, int numFrames)
	: Actor(renderer, texture, frameWidth, frameHeight, numFrames)
{
}

void Item::move(Level& level)
{
	nextFrame();
}

	void Item::onCollide()
	{
		return;
	}

Item::~Item()
{
	// TODO Auto-generated destructor stub
}

void Item::resolveCollision(Actor& other)
{

}
} // namespace jumper
