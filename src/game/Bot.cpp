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

    Bot::Bot(SDL_Renderer *renderer, SDL_Texture *texture, int frameWidth, int frameHeight, int numFrames, Game* game, XML::NPC npc)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames)
    {
        m_physicalProps.setMoveForce(Vector2f(0, 0));
        m_physicalProps.setMaxRunVelocity(50);

        m_game = game;
        //TODO: THIS FOR TESTING AND NEEDS TO BE PARAMETER
        m_health = 2000;

        m_npc = npc;
        if (npc.move_function == "SIN")
        {
            m_move_type=BotType::SIN;
        }
        else if (npc.move_function == "SIN_UP")
        {
            m_move_type=BotType::SIN_UP;
        }
        else if (npc.move_function == "SIN_DOWN")
        {
            m_move_type=BotType::SIN_DOWN;
        }
            else if (npc.move_function == "AI")
        {
            m_move_type=BotType::AI;
        }
        else
        {
            m_move_type=BotType::NO_MOVE;
        }
    }




    void Bot::move(Level &level)
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
                            d_move.setY(-cos(getLiveTime()) * m_npc.move_value * 2.6);
                            break;
                        case BotType::SIN_UP:

                            d_move.setY(-cos(M_PI / 2 + getLiveTime()) * m_npc.move_value * 2.6);
                            break;
                        case BotType::SIN_DOWN:
                            d_move.setY(-cos(-M_PI / 2 + getLiveTime()) * m_npc.move_value * 2.6);
                            break;
                    }
                    d_move.setX(m_npc.speed);
                    physics().setPosition(physics().position() + d_move * dt);
                }
                break;
            case BotType::AI:
                Vector2f d_move;
                d_move.setY(m_game->getPlayerPosition().y());
                d_move.setX(m_npc.speed);
                physics().setPosition(physics().position() + d_move * dt);
                break;
        }
    }


    Bot::~Bot()
    {
        // TODO Auto-generated destructor stub
    }



} /* namespace jumper */
