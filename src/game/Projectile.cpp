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

    SDL_Rect& Projectile::getHitbox()
    {
        SDL_Rect& hitbox = Actor::getHitbox();
        hitbox.x = position().x();
        hitbox.w = (int) fabs(m_lastPosition.x() - position().x());
        return hitbox;
    }

    void Projectile::move(Level& level)
    {
        m_lastPosition = position();
        setPosition(position() + m_direction * 1000 * getElapsedTime());

        // if the projectile exceeds camera boundary, then kill it
        if(!visible()) {
            m_health = 0;
        }
    }

    void Projectile::resolveCollision(Actor& other)
    {
        // TODO: Check if this projectile was shot by player or enemy

        // Hit with player
        if(other.type() == PLAYER) {
            return;
        }

        // Hit with enemy
        if(other.type() == ENEMY) {

        }

        // Kill projectile when it was hit with something
        m_health = 0;
    }
}
