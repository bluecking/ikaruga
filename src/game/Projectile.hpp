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
        Projectile(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

        virtual ~Projectile();

        virtual void move(Level& level);

        const Vector2f& getDirection() const
        { return m_direction; }

        void setDirection(const Vector2f& m_direction)
        { Projectile::m_direction = m_direction; }

        void launch()
        { m_launched = true; }

        virtual void resolveCollision(Actor& other) override;
        virtual const SDL_Rect& getHitbox() override;
    protected:
        Vector2f m_direction;
        bool m_launched;
    private:
        Vector2f m_lastPosition = 0;
    };
}


#endif //JUMPER_PROJECTILE_HPP
