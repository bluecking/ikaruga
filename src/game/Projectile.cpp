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
                           int collisionDamage,
                           float speed)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames, BULLET_HEALTH, collisionDamage),
              m_launched(false), m_originActor(0), m_speed(speed)
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
        nextFrame();
        m_lastPosition = position();

        // Calculate movement of projectile
        Vector2f movement = m_direction * m_speed * getElapsedTime();

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
        if ((m_originActor->type() == PLAYER && (other.type() == ENEMY || other.type() == BOSS)) ||
            ((m_originActor->type() == ENEMY || m_originActor->type() == BOSS) && other.type() == PLAYER))
        {
            m_health = 0;
        }
    }

    void Projectile::onCollide()
    {
        // Kill projectile when colliding with a tile
        m_health = 0;

            return;
        }

    SDL_RendererFlip Projectile::getFlip()
    {
        if (m_direction.x() > 0)
        {
            // No flip necessary shooting backwards
            return SDL_FLIP_NONE;
        }

        // flip texture horizontally if shooting forwards
        return SDL_FLIP_HORIZONTAL;
    }
}
