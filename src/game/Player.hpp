//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_PLAYER_H
#define JUMPER_PLAYER_H

#include <fstream>
#include <iostream>
#include <string>

#include <SDL.h>

#include "Actor.hpp"
#include "Vector.hpp"
#include "Armed.hpp"
#include "Sound.hpp"
#include "PowerUp.hpp"

namespace jumper
{
    class PowerUp;

    /**
     * @brief	A class to represent an animated sprite controlled
     * 			by the user.
     */
    class Player : public Actor, public Armed
    {
    public:

        /**
         * Constructs a player.
         *
         * @param renderer		A pointer to a valid SDL_Renderer struct that is
         * 						used for rendering
         * @param texture		A pointer to a valid SDL_Texture struct
         * @param frameWidth	Frame width of the animation frames
         * @param frameHeight	Frame height of the animation frames
         * @param numFrames		Number of frames
         */
        Player(SDL_Renderer* renderer,
               SDL_Texture* texture,
               Game& game,
               int frameWidth,
               int frameHeight,
               int numFrames,
               int health,
               int collisionDamage);

        /**
         * Moves the player in the given level.
         *
         * @param level			A level object
         */
        virtual void move(Level& level);

        virtual void onCollide();

        virtual void shoot();

        /**
         * @see Actor::resolveCollision(Actor& other)
         */
        virtual void resolveCollision(Actor& other) override;

        const Vector2f& getMoveDirection() const
        {
            return m_moveDirection;
        }

        void setMoveDirection(const Vector2f& moveDirection)
        {
            m_moveDirection = moveDirection;
        }

        /// Prints the player's position to the given stream
        template<typename T>
        friend std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vec);

        /**
         * Sets the sound the player should make, when hit
         *
         * @param soundfile the path to the sound
         */
        void setHitMarkSound(std::string soundfile)
        {
            m_hitMarkSound = Sound(soundfile, SoundType::SOUND);
        }

        /**
         * Sets the volume the hitmarksound should be played with
         *
         * @param volume the volume
         */
        void setHitMarkVolume(int volume)
        {
            m_hitMarkVolume = volume;
        }

        /**
         * plays the hitmarksound
         */
        void playHitMark();

        /**
         * This method iterates through all powerups that the player is owning.
         * It consumes each powerup and removes those that are expired.
         */
        void consumePowerUps();

        int getInitial_health() const
        {
            return m_initial_health;
        }

        bool isGodMode() const
        {
            return m_godMode;
        }

        void setGodMode(bool godMode)
        {
            m_godMode = godMode;
        }

    private:
        Game& m_game;

        Vector2f m_moveDirection;

        int m_initial_health;

        //the sound file
        Sound m_hitMarkSound;

        //the volume of the hitmarksound
        int m_hitMarkVolume;

        /** A flag that is true when the player does not lose health when hit */
        bool m_godMode;

        /** Vector of all powerups that the player is currently owning */
        std::vector<PowerUp*> m_powerUps;

        /**
         * Gets invoked when the player moves up or down.
         * So the player gets rendered with a different texture,
         * and the hitbox is updated to a proper size and position.
         */
        void updateMoveAnimation();
    };
}

#endif //JUMPER_PLAYER_H
