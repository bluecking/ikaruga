/*
 * Item.hpp
 *
 *  Created on: Jan 1, 2016
 *      Author: twiemann
 */

#ifndef SRC_ITEM_HPP_
#define SRC_ITEM_HPP_

#include "Actor.hpp"

namespace jumper
{

/***
 * An Item is a special actor that stays at it's given
 * position and performs an animation. In constrast to
 * an AnimatedRenderable it can perform collision tests.
 */
class Item: public jumper::Actor
{
public:
	Item(SDL_Renderer* renderer, std::string filename);
	Item(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

	virtual void move(Level& level);

	virtual ~Item();
};

} // namespace jumper
#endif /* SRC_ITEM_HPP_ */
