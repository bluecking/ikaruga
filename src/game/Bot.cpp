/*
 * Bot.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#include "Bot.hpp"

using std::cout;
using std::endl;

namespace jumper
{
    Bot::Bot(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames)
    {
        m_physicalProps.setMoveForce(Vector2f(0, 0));
        m_physicalProps.setMaxRunVelocity(50);

        //TODO: THIS FOR TESTING AND NEEDS TO BE PARAMETER
        m_health = 2000;

        // TODO: Delete before pushing
        if((float) rand() / RAND_MAX <= 0.5) {
            m_color = ColorMode::WHITE;
        }
        else {
            m_color = ColorMode::BLACK;
        }

        m_move_type = BotType::SIN_UP;
        m_move_type_height = 25;
        m_speed = 100;
    }

    Bot::~Bot()
    {
        // TODO Auto-generated destructor stub
    }

    void Bot::move(Level& level)
    {
        nextFrame();
        switch (m_move_type)
        {
            case BotType::NO_MOVE:
                break;
            case BotType::SIN:
            case BotType::SIN_UP:
            case BotType::SIN_DOWN:
                float dt = getElapsedTime();
                if (dt > 0)
                {
                    Vector2f d_move;
                    switch (m_move_type)
                    {
                        case BotType::SIN:
                            d_move.setY(-cos(getLiveTime()) * m_move_type_height * 2.6);
                            break;
                        case BotType::SIN_UP:
                            d_move.setY(-cos(3.1415 / 2 + getLiveTime()) * m_move_type_height * 2.6);
                            break;
                        case BotType::SIN_DOWN:
                            d_move.setY(-cos(-3.1415 / 2 + getLiveTime()) * m_move_type_height * 2.6);
                            break;
                    }
                    d_move.setX(m_speed);
                    physics().setPosition(physics().position() + d_move * dt);
                }
                break;
        }
    }

    void Bot::resolveCollision(Actor& other)
    {
        // Hit by player's projectile with same color
        if(other.type() == PROJECTILE && getColor() == other.getColor()) {
            setHit(true);
            takeDamage(500);
        }

        // Hit by actor
        if(other.type() == PLAYER) {
            m_health = 0;
        }
    }
} /* namespace jumper */
