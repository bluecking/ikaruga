/*
 * Collidable.hpp
 *
 *  @date   03.03.2015
 *  @author Benjamin Lücking <bluecking@uos.de>
 *  @author David Rolfes	 <darolfes@uos.de>
 *  @author Nathan Wollek	 <nwollek@uos.de>
 *
 */

#ifndef SRC_GAME_COLLIDABLE_HPP_
#define SRC_GAME_COLLIDABLE_HPP_

#include "Level.hpp"
#include "Collision.hpp"

namespace jumper
{
    class Collidable
    {
    public:
        Collidable();
        virtual ~Collidable();

        virtual void onTileCollision() = 0;

        /**
         * Is invoked if the actor collides with another actor
         * It is pure virtual, since the subclasses react differently on
         * collisions with different actors.
         *
         * @parameter other The actor instance which collided with this instance
         */
        virtual void onActorCollision(Actor& other) = 0;

        virtual SDL_Rect& getHitbox() = 0;

        int getCollisionDamage() const
        {
            return m_collisionDamage;
        }

    protected:
        SDL_Rect m_hitbox;

        /** The hitbox size is resized to this factor */
        float m_hitboxfactor;

        int m_collisionDamage;

        bool m_hit;

        /** The opacity level that is rendered, when a collidable was hit */
        const unsigned char m_opacityLevelWhenHit;
    };

} /* namespace jumper */

#endif /* SRC_GAME_COLLIDABLE_HPP_ */
