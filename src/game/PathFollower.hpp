/*
 * AutoPlayer.hpp
 *
 *  Created on: Jan 8, 2016
 *      Author: twiemann
 */

#ifndef SRC_PATHFOLLOWER_HPP_
#define SRC_PATHFOLLOWER_HPP_

#include <list>

#include "Actor.hpp"

namespace jumper
{

/**
 * @brief An actor class that follows a path within a graph / level
 */
class PathFollower: public Actor
{
public:

	/// Constructor
	PathFollower(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

	/// Destructor.
	virtual ~PathFollower();

	/// Moves the actor along the path
	virtual void move(Level& l);

	/// Sets the path to follow
	virtual void setPath(std::list<Vector2f> path) { m_path = path;}

	/// Renders the actor w.r.t. the path
	virtual void render();
private:

	/// Returns the normalized direction between two path points
	Vector2f getNormalDirection(std::list<Vector2f>::iterator s, std::list<Vector2f>::iterator e);

	/// A list of 2D-Coordinates to follow
	std::list<Vector2f> m_path;

};

} /* namespace jumper */

#endif /* SRC_PATHFOLLOWER_HPP_ */
