/*
 * Bot.hpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#ifndef SRC_BOT_HPP_
#define SRC_BOT_HPP_

#define _USE_MATH_DEFINES

#include "Actor.hpp"
#include "Game.hpp"
#include "Level.hpp"
#include <math.h>
#include <time.h>

#include "../xml/XML.hpp"

namespace jumper
{
    class Game;

    namespace BotType
    {
        enum BotMoveType
        {
            NO_MOVE,
            SIN,
            SIN_UP,
            SIN_DOWN,
            AI
        };
    }

    /**
     * @brief An actor that moves in a level according to a predefined movement pattern.
     * 		  The default implementation switches x-direction when it hits an object.
     */
    class Bot : public Actor
    {
    public:



        void play();


        /**
         * @brief	Constructs a bot from given renderer, texture
         * 			and frame information.
         * @param renderer		A pointer to a SDL renderer struct
         * @param texture		A pointer to valid SDL_Texture struct
         * @param frameWidth	The width of the frames within the texture
         * @param frameHeight	The height of the frames within the texture
         * @param numFrames		The number of frames in the texture
         */

        Bot(SDL_Renderer *renderer,
            SDL_Texture *texture,
            int frameWidth,
            int frameHeight,
            int numFrames,
            Game* game,
            XML::NPC npc,
            int health,
            int collisionDamage,
            ActorType type);


        virtual ~Bot();


        /// Moves the bot in the given \ref level
        virtual void move(Level& level);

        virtual void onCollide();

        /**
         * @see Actor::resolveCollision(Actor& other)
         */
        virtual void resolveCollision(Actor& other) override;
    private:
        const float AI_TRACE_SPEED=0.7;
        int m_move_type;
        int m_move_type_height;
        int m_speed;
        XML::NPC m_npc;

        Game* m_game;

        const int DAMAGE_BY_PROJECTILE = 500;
    };

} /* namespace jumper */

#endif /* SRC_BOT_HPP_ */
