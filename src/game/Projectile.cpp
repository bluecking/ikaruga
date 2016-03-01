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

        //setPosition(position() + level.collide(position(), w(), h(), m_direction * 1000 * getElapsedTime(), this));

        float elapsedTime = getElapsedTime();

        //level.collide(position(), w(), h(), m_direction * 1000 * elapsedTime, this);
        setPosition(position() + m_direction * 1000 * elapsedTime);



        // if the projectile exceeds camera boundary, then kill it
        if (!visible())
        {
            m_health = 0;
        }
    }

    void Projectile::resolveCollision(Actor& other)
    {
        // TODO: Check if this projectile was shot by player or enemy

        // Hit with player
        if (other.type() == PLAYER)
        {
            return;
        }

        // Hit with enemy
        if (other.type() == ENEMY)
        {

        }

        // Kill projectile when it was hit with something
        m_health = 0;
    }

        void Projectile::onCollide()
        {
            //m_health = 0;
            return;
        }
}
