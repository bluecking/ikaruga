/*
 * Bot.hpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#ifndef SRC_BOT_HPP_
#define SRC_BOT_HPP_

#include "Actor.hpp"
#include "Level.hpp"
#include <math.h>
#include <time.h>

namespace jumper
{
    namespace BotType
    {
        enum BotMoveType
        {
            NO_MOVE,
            SIN,
        };
    }
/**
 * @brief An actor that moves in a level according to a predefined movement pattern.
 * 		  The default implementation switches x-direction when it hits an object.
 */
    class Bot : public Actor
    {
    public:


        /***
         * @brief 	Constructs a bot from the given \ref filename
         * 			for the internal \ref renderer
         * @param renderer		A pointer to a SDL renderer struct
         * @param filename		A filename with animation definitions
         */
        Bot(SDL_Renderer *renderer, std::string filename);

        /**
         * @brief	Constructs a bot from given renderer, texture
         * 			and frame information.
         * @param renderer		A pointer to a SDL renderer struct
         * @param texture		A pointer to valid SDL_Texture struct
         * @param frameWidth	The width of the frames within the texture
         * @param frameHeight	The height of the frames within the texture
         * @param numFrames		The number of frames in the texture
         */
        Bot(SDL_Renderer *renderer, SDL_Texture *texture, int frameWidth, int frameHeight, int numFrames);

        virtual ~Bot();

        /// Moves the bot in the given \ref level
        virtual void move(Level &level);

    private:
        int m_move_type;
        int m_move_type_speed;
        int m_speed;
    };

} /* namespace jumper */

#endif /* SRC_BOT_HPP_ */
