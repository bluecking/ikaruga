/**
 * Projectile.cpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include "Projectile.hpp"

namespace jumper {
    Projectile::Projectile(SDL_Renderer *renderer, SDL_Texture *texture, int frameWidth, int frameHeight, int numFrames)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames), m_launched(false) { }

    Projectile::~Projectile() { }

    void Projectile::move(Level &level) {
        setPosition(position() + (m_direction * 1000 * getElapsedTime()));
    }
}
