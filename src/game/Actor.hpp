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
        PLAYER,
        PROJECTILE,
        BOSS,
        POWERUP
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
        Actor(SDL_Renderer* renderer,
              SDL_Texture* texture,
              int frameWidth,
              int frameHeight,
              int numFrames,
              int health,
              int collisionDamage);

        virtual ~Actor();

        virtual void move(Level& level) = 0;

        virtual void onCollide() = 0;

        /**
         * Is invoked if the actor collides with another actor
         * It is pure virtual, since the subclasses react differently on
         * collisions with different actors.
         *
         * @parameter other The actor instance which collided with this instance
         */
        virtual void resolveCollision(Actor& other) = 0;

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

        const ActorType& type() { return m_type; }

        void setType(ActorType t) { m_type = t; }

        void setColorOffset(const Vector2f& colorOffset) { m_colorOffset = colorOffset; }

        const Vector2f& getColorOffset() const { return m_colorOffset; }

        void toggleColor();

        const ColorMode::ColorMode& getColor() const { return m_color; }

        void setColor(const ColorMode::ColorMode& m_color) { Actor::m_color = m_color; }

        /**
         * Returns true, if the actor is visible (in camera rect)
         */
        bool visible();

        void takeDamage(int damage);

        int getHealth() const;

        virtual SDL_Rect& getHitbox();

        void setHit(bool hit)
        {
            m_hit = hit;
        }

        bool isHit() const {
            return m_hit;
        }

        void setLiveTime();

        /**
         * the sound when this thing explodes
         *
         * @param explosionSoundFilename the filepath to the explosion sound
         */
        void setExplosionSound(std::string explosionSoundFilename)
        {
            m_explosionSound = Sound(explosionSoundFilename, SoundType::SOUND);
        };

        /**
         * the explosion of the volume
         *
         * @param volume
         */
        void setExplosionVolume(int volume) {
            m_explosionVolume = volume;
        }

        void setScoreValue(int value)
        {
            m_scoreValue = value;
        }

        void setKilled(bool killed) {
            m_isKilled = killed;
        }

        bool isKilled() const
        {
            return m_isKilled;
        }


        virtual void setHealth(int health)
        {
            m_health = health;
        }

        int getScoreValue() const
        {
            return m_scoreValue;
        }

        int getCollisionDamage() const
        {
            return m_collisionDamage;
        }

        void setCollisionDamage(int collisionDamage)
        {
            m_collisionDamage = collisionDamage;
        }

        void dropPowerUp();

        void setIsKilled(bool isKilled)
        {
            m_isKilled = isKilled;
        }

        void playExplosionSound();

    protected:
        int m_scoreValue = 0;

        int m_health;

        int m_collisionDamage;

        bool m_isKilled;

        //the explosion sound
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

        SDL_Rect m_hitbox;

        bool m_hit = false;

        //Explosion Volume
        int m_explosionVolume;

        /**
         * @return Whether or not a texture flip is necessary
         */
        virtual SDL_RendererFlip getFlip();
    private:
        /** The hitbox size is reduced to this factor */
        const float HITBOXFACTOR = 0.8;

        /** The opacity level that is rendered, when an actor was hit */
        const unsigned char OPACITY_LEVEL_WHEN_HIT = 50;

        void renderHitbox();
    };

} /* namespace jumper */

#endif /* SRC_ACTOR_HPP_ */
