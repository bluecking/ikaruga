/*
 * TexturedLayer.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#include "TexturedLayer.hpp"

#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

namespace jumper
{


TexturedLayer::TexturedLayer(SDL_Renderer* renderer)
	: StaticRenderable(renderer)
{
	m_scrollSpeed = 1.0f;
}

TexturedLayer::TexturedLayer(SDL_Renderer* renderer, SDL_Texture* texture)
	: StaticRenderable(renderer, texture)
{
	m_scrollSpeed = 1.0f;
}

void TexturedLayer::render()
{
	SDL_Rect target;

	// Determine x and y offset
	int xOff = (std::abs(m_camera.x()) % m_sourceRect.w) * m_scrollSpeed;
	int yOff = (std::abs(m_camera.y()) % m_sourceRect.h) * m_scrollSpeed;

	// Handle sign (why is there no signum function in C++?
	if(m_camera.x() > 0)
	{
		xOff = -xOff;
	}


	if(m_camera.y() > 0)
	{
		yOff = -yOff;
	}

	// Start rendering
	target.x = xOff;
	target.y = yOff;
	target.w = m_sourceRect.w;
	target.h = m_sourceRect.h;

	while(target.y < m_camera.h())
	{
		while(target.x < m_camera.w())
		{

			SDL_RenderCopy(m_renderer, m_texture, &m_sourceRect, &target);
			target.x += m_sourceRect.w;
		}
		target.y += m_sourceRect.h;
		target.x = xOff;
		//cout << target.y << endl;
	}



}

TexturedLayer::~TexturedLayer()
{
	// TODO Auto-generated destructor stub
}

void TexturedLayer::setScrollSpeed(float speed)
{
	m_scrollSpeed = speed;
}

} /* namespace jumper */
