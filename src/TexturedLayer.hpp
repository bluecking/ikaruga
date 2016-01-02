/*
 * TexturedLayer.hpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#ifndef SRC_TEXTUREDLAYER_HPP_
#define SRC_TEXTUREDLAYER_HPP_

#include "StaticRenderable.hpp"

namespace jumper
{

class TexturedLayer: public StaticRenderable
{
public:
	TexturedLayer(SDL_Renderer* renderer);
	TexturedLayer(SDL_Renderer* renderer, SDL_Texture* texture);

	virtual void render();

	virtual ~TexturedLayer();
};

} /* namespace jumper */

#endif /* SRC_TEXTUREDLAYER_HPP_ */
