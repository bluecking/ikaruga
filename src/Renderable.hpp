//
// Created by isaak on 25.11.15.
//

#ifndef JUMPER_RENDERABLE_H
#define JUMPER_RENDERABLE_H

#include <SDL.h>
#include <string>
#include "Camera.hpp"

namespace jumper
{

class Renderable
{

public:

    /**
     * @brief Custom constructor
     * @param SDL_Renderer
     */
    Renderable(SDL_Renderer *m_renderer);

    /**
     * @brief   Renderer getter
     * @return  SDL_Renderer
     */
    SDL_Renderer *getRenderer() const;

    /**
    * @brief   Renders the object.
    */
    virtual void render() = 0;

    /// Returns the with of the rendered object
    int w() const;

    /// Returns the height of the rendered object
    int h() const;

protected:

    /**
     * Generates a SDL_Texture struct from the given files.
     *
     * @param 	texFileName		An image file to load into the texture
     * @param 	keyR			Red component of the key color
     * @param 	keyG			Green component of the key color
     * @param 	keyB			Blue component of the key color
     *
     * @return SDL_Textur or NULL if texture generation failed.
     */
    SDL_Texture* loadTexture(std::string texFileName,
                             unsigned char keyR,
                             unsigned char keyG,
                             unsigned char keyB);

    /**
     * Generates a SDL_Texture struct from the given file
     *
     * @param 	texFileName		An image file to load into the texture
     * @return SDL_Textur or NULL if texture generation failed.
     */
    SDL_Texture* loadTexture(std::string texFileName);


    /// Renderer
    SDL_Renderer*		m_renderer;

    /// A texture object
    SDL_Texture*		m_texture;

	/// Source rect in the texture
	SDL_Rect 			m_sourceRect;
};

} /* namespace jumper */

#endif //JUMPER_RENDERABLE_H
