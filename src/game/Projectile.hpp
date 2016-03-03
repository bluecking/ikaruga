/**
 * Projectile.hpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef JUMPER_PROJECTILE_HPP
#define JUMPER_PROJECTILE_HPP

#include "Level.hpp"
#include "Game.hpp"

namespace jumper
{
    class Projectile : public Actor
    {
    public:
        Projectile(SDL_Renderer* renderer,
                   SDL_Texture* texture,
                   int frameWidth,
                   int frameHeight,
                   int numFrames,
                   int collisionDamage,
                   float speed);

        Actor* getOriginActor() const
        { return m_originActor; }

        void setOriginActor(Actor* m_originActor)
        { Projectile::m_originActor = m_originActor; }

        virtual ~Projectile();

        virtual void move(Level& level) override;

        virtual void onTileCollision() override;

        const Vector2f& getDirection() const
        { return m_direction; }

        void setDirection(const Vector2f& m_direction)
        { Projectile::m_direction = m_direction; }

        void launch()
        { m_launched = true; }

        /**
         * @see Actor::onActorCollision(Actor& other)
         */
        void onActorCollision(Actor& other) override;

        /**
         * @return Whether or not a texture flip is necessary
         */
        virtual SDL_RendererFlip getFlip() override;

        virtual SDL_Rect& getHitbox() override;
    protected:
        Vector2f m_direction;
        bool m_launched;
        int m_collisionDamage;
        float m_speed;
    private:
        Vector2f m_lastPosition = 0;
        Actor* m_originActor;
    };
}


#endif //JUMPER_PROJECTILE_HPP
