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
#include <thread>
#include <chrono>

namespace jumper
{

/***
 * A class the represents a sprite that is moving and implements
 * collision detection.
 */
class Actor : public AnimatedRenderable
{
public:

	/***
	 * Constructs an actor from the given \ref filename
	 * for the internal \ref renderer
	 * @param renderer		A pointer to a SDL renderer struct
	 * @param filename		A filename with animation definitions
	 */
	Actor(SDL_Renderer* renderer, std::string filename);


	Actor(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);
	virtual ~Actor();

	virtual void move(Level& level) = 0;
	virtual void getCollision(Actor& other);

	virtual void render();

	void setPhysics(PlayerProperty p);
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

	void start(Level& level);

	void setFocus(bool focus);

	bool hasFocus();
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

    std::thread			m_thread;

    bool				m_focus;

};

} /* namespace jumper */

#endif /* SRC_ACTOR_HPP_ */
