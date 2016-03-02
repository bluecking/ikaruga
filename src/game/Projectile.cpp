/**
 * Projectile.cpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include "Projectile.hpp"

namespace jumper
{
    const int BULLET_HEALTH = 32767;

    Projectile::Projectile(SDL_Renderer* renderer,
                           SDL_Texture* texture,
                           int frameWidth,
                           int frameHeight,
                           int numFrames,
                           int collisionDamage)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames, BULLET_HEALTH, collisionDamage),
              m_launched(false), m_originActor(0)
    {
        m_hitbox.h = frameHeight;
        m_collisionDamage = collisionDamage;
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

        // Calculate movement of projectile
        Vector2f movement = m_direction * 1000 * getElapsedTime();

        // Check collision with tiles
        level.collide(position(), w(), h(), movement, this);

        // Set new projectile position regardless of collision
        setPosition(position() + movement);

        // if the projectile exceeds camera boundary, then kill it
        if (!visible())
        {
            m_health = 0;
        }
    }

    void Projectile::resolveCollision(Actor& other)
    {
        // TODO: Check if this projectile was shot by player or enemy

        if (other.type() == PROJECTILE)
        {
            return;
        }

        // Hit with player
        if (other.type() == PLAYER)
        {
            if (m_originActor->type() == PLAYER)
            {
                return;
            }
        }

        // Hit with enemy
        if (other.type() == ENEMY || other.type() == BOSS)
        {
            if (m_originActor->type() == ENEMY || other.type() == BOSS)
            {
                return;
            }
        }

        // Kill projectile when it was hit with something
        m_health = 0;
    }

        void Projectile::onCollide()
        {
            // Kill projectile when colliding with a tile
            m_health = 0;

            return;
        }
}
