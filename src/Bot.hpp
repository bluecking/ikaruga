/*
 * Bot.hpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#ifndef SRC_BOT_HPP_
#define SRC_BOT_HPP_

#include "Actor.hpp"
#include "Level.hpp"

namespace jumper
{

/*
 *
 */
class Bot : public Actor
{
public:
	Bot(SDL_Renderer* renderer, std::string filename);
	Bot(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);
	virtual ~Bot();

	virtual void move(Level& level);

private:
	void bounce();

	Vector2f m_bouncePos;
};

} /* namespace jumper */

#endif /* SRC_BOT_HPP_ */
