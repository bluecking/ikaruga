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

namespace jumper {
    enum ActorType {
        ENEMY,
        PLATFORM,
        ITEM,
        PUZZLEBOX,
        ACTOR,
        PROJECTILE
    };

    namespace ColorMode {
        enum ColorMode {
            NONE,
            BLACK,
            WHITE
        };
    }

    /**
     * @brief A class the represents a sprite that is moving and implements
     * collision detection.
     */
    class Actor : public AnimatedRenderable {
    public:

        /**
         * Constructs an actor from the given \ref filename
         * for the internal \ref renderer
         * @param renderer		A pointer to a SDL renderer struct
         * @param filename		A filename with animation definitions
         */
        Actor(SDL_Renderer *renderer, SDL_Texture *texture, int frameWidth, int frameHeight, int numFrames);

        virtual ~Actor();

        /**
         * moves to another level
         *
         * @param the level to move to
         */
        virtual void move(Level &level) = 0;

        /**
         * gets the collision with another actor
         *
         * @param other the other actor to get the collision from
         */
        virtual Collision getCollision(Actor &other);

        /**
         * resolves a collision with another actor
         *
         * @param other the other actor to resolve collision with
         */
        virtual void resolveCollision(Actor &other);

        /**
         * renders the Actor
         */
        virtual void render();

        /**
         * Sets the player's Physics
         *
         * @oaram p Players properties
         */
        void setPhysics(PlayerProperty p);

        /**
         * Sets the player's position
         *
         * @oaram pos Position of the Player
         */
        void setPosition(Vector2f pos);

        /***
         * Returns the player's current position
         *
         * @returns the players current position
         */
        Vector2f position();

        /**
         * Returns the player's physical properties
         *
         * @returns the players properties
         */
        PlayerProperty &physics();

        /**
         * sets the focus to this actor
         *
         * @param focus true, when set the focus to this actor, false when not
         */
        void setFocus(bool focus);

        /**
         * check if this actor has focus
         *
         * @returns true if this actor has focus, false if not
         */
        bool hasFocus();

        /**
         * returns the actors type
         *
         * @returns the actors type
         */
        ActorType type() { return m_type; }

        /**
         * sets the actors type
         *
         * @param t the actors type
         */
        void setType(ActorType t) { m_type = t; }

        /**
         * sets the actors type
         *
         * @param t the actors type
         */
        void setColorOffset(const Vector2f &colorOffset) { m_colorOffset = colorOffset; }

        /**
         * get the color offset
         *
         * @returns the color offset of the actor
         */
        const Vector2f &getColorOffset() const { return m_colorOffset; }

        /**
         * toggles the color
         */
        void toggleColor();

        /**
         * get the color
         *
         * @returns the current color
         */
        const ColorMode::ColorMode &getColor() const { return m_color; }

        /**
         * sets the color
         *
         * @param m_color the color
         */
        void setColor(const ColorMode::ColorMode &m_color) { Actor::m_color = m_color; }

        /**
         * Returns true, if the actor is visible (in camera rect)
         */
        bool visible();

        /**
         * lets the actor take damate
         *
         * @param damage the damage the actor should take
         */
        void takeDamage(int damage);

        /**
         * returns the health of the actor
         *
         * @returns the health of the actor
         */
        int getHealth();

    protected:

        //the elapsed time in the level
        float getElapsedTime();

        //the time the level is on screen
        float getLiveTime();

        /// The physical properties of the player
        PlayerProperty m_physicalProps;

        //the tick counter startet
        Uint32 m_startTicks;

        //the spawn started
        Uint32 m_spawnTime;

        //true if the actor has focus, false if not
        bool m_focus;

        //type of the current actor
        ActorType m_type;

        //the color of the actor
        ColorMode::ColorMode m_color;

        //the color offset of the actor
        Vector2f m_colorOffset;

        //the health of the actor
        int m_health;
    };
} /* namespace jumper */

#endif /* SRC_ACTOR_HPP_ */
