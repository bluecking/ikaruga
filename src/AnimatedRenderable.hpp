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
 * Base class of renderables with several animation frames
 */
class AnimatedRenderable: public Renderable
{
public:

	/***
	 * Contructs an animated renderable from the given \ref filename
	 * for the internal \ref renderer
	 * @param renderer		A pointer to a SDL renderer struct
	 * @param filename		A filename with animation definitions
	 */
	AnimatedRenderable(SDL_Renderer* renderer, std::string filename);

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

protected:

	///	Number of frames in the animation
	int				m_numFrames;

	/// Current frame number
	int				m_currentFrame;

	/// The width of a frame
	int 			m_frameWidth;

	/// The height of a frame
	int				m_frameHeight;

};

} /* namespace jumper */

#endif /* SRC_ANIMATEDRENDERABLE_HPP_ */
