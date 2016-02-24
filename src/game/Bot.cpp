/*
 * Bot.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#include "Bot.hpp"


#include <iostream>

using std::cout;
using std::endl;

namespace jumper
{

    Bot::Bot(SDL_Renderer *renderer, std::string filename)
            : Actor(renderer, filename)
    {
        m_physicalProps.setMoveForce(Vector2f(0, 0));
        m_physicalProps.setMaxRunVelocity(50);

        //TODO: THIS FOR TESTING AND NEEDS TO BE PARAMETER
        m_health = 10000;
    }

    Bot::Bot(SDL_Renderer *renderer, SDL_Texture *texture, int frameWidth, int frameHeight, int numFrames)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames)
    {
        m_physicalProps.setMoveForce(Vector2f(0, 0));
        m_physicalProps.setMaxRunVelocity(50);

        //TODO: THIS FOR TESTING AND NEEDS TO BE PARAMETER
        m_health = 10000;

        m_move_type = BotType::SIN;
        m_move_type_speed = 50;
        m_speed = 100;
    }

    Bot::~Bot()
    {
    }

    void Bot::move(Level &level)
    {
        nextFrame();

        switch (m_move_type)
        {
            case BotType::NO_MOVE:
                break;
            case BotType::SIN:
                float dt = getElapsedTime();
                if (dt > 0)
                {
                    Vector2f d_move;
                    d_move.setY(m_move_type_speed * sin(1.5 * clock() / CLOCKS_PER_SEC) * 3.1415);
                    d_move.setX(m_speed);
                    physics().setPosition(physics().position() + d_move * dt);
                }
                break;
        }
    }

} /* namespace jumper */
