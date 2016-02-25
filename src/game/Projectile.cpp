/**
 * Projectile.cpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include "Projectile.hpp"

namespace jumper
{
    Projectile::Projectile(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames), m_launched(false)
    {
        m_hitbox.h = frameHeight;
    }

    Projectile::~Projectile()
    { }

    const SDL_Rect& Projectile::getHitbox()
    {
        SDL_Rect hitbox = Actor::getHitbox();
        hitbox.w *= 2;

        return hitbox;
    }

    void Projectile::move(Level& level)
    {
        setPosition(position() + m_direction * 1000 * getElapsedTime());
    }
}
