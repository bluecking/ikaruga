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
    Renderable(SDL_Renderer *m_renderer) : m_renderer(m_renderer) { };

    /**
     * @brief   Renderer getter
     * @return  SDL_Renderer
     */
    SDL_Renderer *getRenderer() const;

    /**
    * @brief   Renders the object.
    */
    virtual void render(Camera& cam) = 0;

    /**
     * @brief Generates a SDL_Texture struct from the given files.
     * @param std::string texFileName
     * @param unsigned char m_keyR
     * @param unsigned char m_keyG
     * @param unsigned char m_keyB
     * @return SDL_Textur or NULL if texture generation failed.
     */
    SDL_Texture* loadTexture(std::string texFileName,
                             unsigned char m_keyR,
                             unsigned char m_keyG,
                             unsigned char m_keyB);

    SDL_Texture* loadTexture(std::string texFileName);

private:

    /// Renderer
    SDL_Renderer*		m_renderer;

};

} /* namespace jumper */

#endif //JUMPER_RENDERABLE_H
