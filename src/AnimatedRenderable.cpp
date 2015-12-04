/*
 * AnimatedRenderable.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: twiemann
 */

#include "AnimatedRenderable.hpp"

#include <fstream>

namespace jumper
{

AnimatedRenderable::AnimatedRenderable(SDL_Renderer* renderer, std::string filename)
	: Renderable(renderer), m_numFrames(0), m_currentFrame(0), m_frameWidth(0), m_frameHeight(0)
{
	std::ifstream ifs(filename.c_str());
	std::string textureFileName;
	if(ifs.good())
	{
		ifs >> textureFileName >> m_frameWidth >> m_frameHeight >> m_numFrames;
		m_texture = loadTexture(textureFileName);
	}
	else
	{
		std::cout << "Unable to open file " << filename << std::endl;
	}

	// Initialize source recnt
	m_sourceRect.x = 0;
	m_sourceRect.y = 0;
	m_sourceRect.w = m_frameWidth;
	m_sourceRect.h = m_frameHeight;

}

AnimatedRenderable::~AnimatedRenderable() {}


void AnimatedRenderable::nextFrame()
{
	// Check and increase frame counter
	if(m_currentFrame + 1 < m_numFrames)
	{
		m_currentFrame++;
	}
	else
	{
		m_currentFrame = 0;
	}

	// Setup source rect
	m_sourceRect.x = m_currentFrame * m_frameWidth;
}

} /* namespace jumper */
