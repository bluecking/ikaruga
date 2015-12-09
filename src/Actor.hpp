/*
 * Actor.hpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#ifndef SRC_ACTOR_HPP_
#define SRC_ACTOR_HPP_

#include "AnimatedRenderable.hpp"
#include "PlayerProperty.hpp"
#include "WorldProperty.hpp"
#include "Level.hpp"

#include <string>

namespace jumper
{

/*
 *
 */
class Actor : public AnimatedRenderable
{
public:
	Actor(SDL_Renderer* renderer, std::string filename);
	virtual ~Actor();

	virtual void move(WorldProperty& prop) = 0;

	virtual void getCollision(Actor& other);
	virtual void getCollision(Level& level);

	virtual void render();

	/**
	 * Sets the player's position
	 */
	void setPosition(Vector2f pos);

	/***
	 * Returns the player's current position
	 */
	Vector2f position();

	/**
	 * Returns the player's physical properties
	 */
	PlayerProperty &physics();

	/**
	 * True, if the player touches ground
	 */
	bool onGround() const;

	/**
	 * Sets the on ground flag to the given status
	 */
	void setOnGround(bool m_onGround);

	/**
	 * Sets the jump state
	 */
	void setJumping(bool jump);

	/**
	 * Returns the jump state
	 */
	bool jumping();

	/**
	 * Retruns the pixel position at which jumping was started
	 */
	int jumpStart();

	void wantsToJump(bool j);

protected:

	float getElapsedTime();

    /// True if the player touches ground
    bool     			m_onGround;

    /// True if the player is jumping
    bool     			m_jumping;

    /// Indicates if the actors wants to start jumping
    bool				m_wantsToJump;

    /// Pixel position where jumping has started
    int     			m_jumpStart;

    /// The physical properties of the player
    PlayerProperty 		m_physicalProps;

    Uint32				m_startTicks;
};

} /* namespace jumper */

#endif /* SRC_ACTOR_HPP_ */
