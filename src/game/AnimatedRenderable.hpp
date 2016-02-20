/*
 * AnimatedRenderable.hpp
 *
 *  Created on: Dec 4, 2015
 *      Author: twiemann
 */

#ifndef SRC_ANIMATEDRENDERABLE_HPP_
#define SRC_ANIMATEDRENDERABLE_HPP_

#include "Renderable.hpp"

#include <string>
#include <iostream>

namespace jumper
{

/**
 * @brief Base class of renderables with several animation frames
 */
class AnimatedRenderable: public Renderable
{
public:

	/***
	 * Constructs an animated renderable from the given \ref filename
	 * for the internal \ref renderer
	 * @param renderer		A pointer to a SDL renderer struct
	 * @param filename		A filename with animation definitions
	 */
	AnimatedRenderable(SDL_Renderer* renderer, std::string filename);

	/***
	 * Constructs an animated renderable from given renderer, texture
	 * and frame information.
	 * @param renderer		A pointer to a SDL renderer struct
	 * @param texture		A pointer to valid SDL_Texture struct
	 * @param frameWidth	The width of the frames within the texture
	 * @param frameHeight	The height of the frames within the texture
	 * @param numFrames		The number of frames in the texture
	 */
	AnimatedRenderable(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);


	/**
	 * Destructor.
	 */
	virtual ~AnimatedRenderable();

	/**
	 * Renders the current frame
	 */
	virtual void render() = 0;

	/**
	 * Moves the source rect to the next frame
	 */
	void nextFrame();

	/**
	 * Sets frames per second for animation
	 */
	void setFPS(int frames);

protected:

	///	Number of frames in the animation
	int				m_numFrames;

	/// Current frame number
	int				m_currentFrame;

	/// The width of a frame
	int 			m_frameWidth;

	/// The height of a frame
	int				m_frameHeight;

	/// Ticks count when the last frame was rendered
	Uint32			m_lastRenderTicks;

	/// Timeout between frames
	Uint32			m_frameTimeout;

};

} /* namespace jumper */

#endif /* SRC_ANIMATEDRENDERABLE_HPP_ */
