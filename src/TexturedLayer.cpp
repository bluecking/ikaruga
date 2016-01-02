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
}

TexturedLayer::TexturedLayer(SDL_Renderer* renderer, SDL_Texture* texture)
	: StaticRenderable(renderer, texture)
{
}

void TexturedLayer::render()
{
	SDL_Rect target;

	// Determine x and y offset
	int xOff = (std::abs(m_camera.x()) % m_sourceRect.w) * 1.2;
	int yOff = (std::abs(m_camera.y()) % m_sourceRect.h) * 1.2;

	// Handle sign (why is there no signum function in C++?
	if(m_camera.x() > 0)
	{
		xOff = -xOff;
	}
	else
	{
		// Handle remainder of texture
		xOff = -(m_sourceRect.w - xOff);
	}

	if(m_camera.y() > 0)
	{
		yOff = -yOff;
	}
	else
	{
		// Handle remainder of texture
		yOff = -(m_sourceRect.h - yOff);
	}

	yOff = 0;

	// Start rendering
	target.x = xOff;
	target.y = yOff;
	target.w = m_sourceRect.w;
	target.h = m_sourceRect.h;

	cout << target.x << " " << target.y << " " 	<< target.w << " " << target.h << endl;

	while(target.x < m_camera.w())
	{
		cout << target.x << endl;
		SDL_RenderCopy(m_renderer, m_texture, &m_sourceRect, &target);
		target.x += m_sourceRect.w;
	}


}

TexturedLayer::~TexturedLayer()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */
