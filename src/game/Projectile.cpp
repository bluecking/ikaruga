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
        hitbox.w = (int) fabs(m_lastPosition.x() - position().x());
//        std::cout << hitbox.x << "+" << hitbox.w << "=" << hitbox.x + hitbox.w << std::endl;
        return hitbox;
    }

    void Projectile::move(Level& level)
    {
        m_lastPosition = position();
        setPosition(position() + m_direction * 1000 * getElapsedTime());
    }

    void Projectile::resolveCollision(Actor& other)
    {
        switch(other.type()) {
            case ACTOR:
                return;
        }
        this->m_hit = true;
    }
}
