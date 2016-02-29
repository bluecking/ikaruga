/*
 * Actor.hpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#ifndef SRC_ACTOR_HPP_
#define SRC_ACTOR_HPP_

#include "AnimatedRenderable.hpp"
#include "PlayerProperty.hpp"
#include "WorldProperty.hpp"
#include "Level.hpp"
#include "Collidable.hpp"

#include <string>
#include <thread>
#include <chrono>
#include "Sound.hpp"

namespace jumper
{
    enum ActorType
    {
        ENEMY,
        PLATFORM,
        ITEM,
        PUZZLEBOX,
        ACTOR,
        PROJECTILE
    };

    namespace ColorMode
    {
        enum ColorMode
        {
            NONE,
            BLACK,
            WHITE
        };
    }

    /**
     * @brief A class the represents a sprite that is moving and implements
     * collision detection.
     */
    class Actor : public AnimatedRenderable
    {
    public:

        /**
         * Constructs an actor from the given \ref filename
         * for the internal \ref renderer
         * @param renderer		A pointer to a SDL renderer struct
         * @param filename		A filename with animation definitions
         */
        Actor(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

        virtual ~Actor();

        virtual void move(Level& level) = 0;

        virtual Collision getCollision(Actor& other);

        virtual void resolveCollision(Actor& other);

        virtual void render();

        void setPhysics(PlayerProperty p);

        /**
         * Sets the player's position
         */
        void setPosition(Vector2f pos);

        /***
         * Returns the player's current position
         */
        Vector2f position();

        /**
         * Returns the player's physical properties
         */
        PlayerProperty& physics();

        void setFocus(bool focus);

        bool hasFocus();

        ActorType type()
        { return m_type; }

        void setType(ActorType t)
        { m_type = t; }

        void setColorOffset(const Vector2f& colorOffset)
        { m_colorOffset = colorOffset; }

        const Vector2f& getColorOffset() const
        { return m_colorOffset; }

        void toggleColor();

        const ColorMode::ColorMode& getColor() const
        { return m_color; }

        void setColor(const ColorMode::ColorMode& m_color)
        { Actor::m_color = m_color; }

        /**
         * Returns true, if the actor is visible (in camera rect)
         */
        bool visible();

        void takeDamage(int damage);

        int getHealth();

        void setLiveTime();

        void setExplosionSound(std::string explosionSoundFilename);

    protected:

        Sound m_explosionSound;

        float getElapsedTime();

        float getLiveTime();

        /// The physical properties of the player
        PlayerProperty m_physicalProps;

        Uint32 m_startTicks;

        Uint32 m_spawnTime;

        bool m_focus;

        ActorType m_type;

        ColorMode::ColorMode m_color;

        Vector2f m_colorOffset;

        int     m_health;

        Level *m_level;


    };

} /* namespace jumper */

#endif /* SRC_ACTOR_HPP_ */
