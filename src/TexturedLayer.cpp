/*
 * TexturedLayer.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#include "TexturedLayer.hpp"

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
}

TexturedLayer::~TexturedLayer()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */
