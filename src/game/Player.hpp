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

namespace jumper
{
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
        Player(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

        /**
         * Moves the player in the given level.
         *
         * @param level			A level object
         */
        virtual void move(Level& level);

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
        void setHitMarkSound(std::string soundfile);

    private:
        Vector2f m_moveDirection;

        //the sound file
        Sound m_hitMarkSound;
    public:
        virtual void shoot();
        void updateMoveAnimation();
    };
}

#endif //JUMPER_PLAYER_H
