//
// Created by isaak on 25.11.15.
//

#include <SDL_image.h>
#include <iostream>
#include "Renderable.hpp"
namespace jumper
{
SDL_Renderer *Renderable::getRenderer() const
{
    return m_renderer;
}

SDL_Texture *Renderable::loadTexture(std::string texFileName,
                                     unsigned char keyR,
                                     unsigned char keyG,
                                     unsigned char keyB)
{
    // The loaded texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(texFileName.c_str());
    if( loadedSurface == NULL )
    {
        std::cout << "Unable to load image! SDL_image Error: " <<  IMG_GetError() << std::endl;
    }
    else
    {
        // Set keying color
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, keyR, keyG, keyB) );

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(getRenderer(), loadedSurface );
        if( newTexture == NULL )
        {
            std::cout <<  "Unable to create texture from! SDL Error: " << texFileName <<  SDL_GetError() << std::endl;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}


SDL_Texture *Renderable::loadTexture(std::string texFileName)
{
    // The loaded texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(texFileName.c_str());
    if( loadedSurface == NULL )
    {
        std::cout << "Unable to load image! SDL_image Error: " <<  IMG_GetError() << std::endl;
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(getRenderer(), loadedSurface );
        if( newTexture == NULL )
        {
            std::cout <<  "Unable to create texture from! SDL Error: " << texFileName <<  SDL_GetError() << std::endl;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

} /* namespace jumper */
