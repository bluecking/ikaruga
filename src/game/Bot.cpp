/*
 * Bot.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#include "Bot.hpp"
#include "Game.hpp"

using std::cout;
using std::endl;

namespace jumper
{
    Bot::Bot(SDL_Renderer* renderer,
             SDL_Texture* texture,
             int frameWidth,
             int frameHeight,
             int numFrames,
             Game* game,
             XML::NPC npc,
             int health,
             int collisionDamage)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames, health, collisionDamage)
    {
        m_type = ActorType::ENEMY;
        m_physicalProps.setMoveForce(Vector2f(0, 0));
        m_physicalProps.setMaxRunVelocity(50);

        m_game = game;
        //TODO: THIS FOR TESTING AND NEEDS TO BE PARAMETER

        m_type = ActorType::ENEMY;

        m_npc = npc;
        if (npc.move_function == "SIN")
        {
            m_move_type = BotType::SIN;
        }
        else if (npc.move_function == "SIN_UP")
        {
            m_move_type = BotType::SIN_UP;
        }
        else if (npc.move_function == "SIN_DOWN")
        {
            m_move_type = BotType::SIN_DOWN;
        }
        else if (npc.move_function == "AI")
        {
            m_move_type = BotType::AI;
        }
        else
        {
            m_move_type = BotType::NO_MOVE;
        }
        m_move_type_height = 25;
        m_speed = 100;
    }

    void Bot::move(Level& level)
    {
        nextFrame();
        float dt = getElapsedTime();
        Vector2f d_move;
        switch (m_move_type)
        {
            case BotType::NO_MOVE:
                break;
            case BotType::AI:
            {
                float ds = (m_game->getPlayerPosition().y()-physics().position().y())*AI_TRACE_SPEED;
                d_move.setY(ds);
                d_move.setX(m_npc.speed);
                physics().setPosition(physics().position() + d_move * dt);
                break;
            }
            case BotType::SIN:
            case BotType::SIN_UP:
            case BotType::SIN_DOWN:
            {
                if (dt > 0)
                {

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
            }
        }

        // remove bots
        if (position().x() + Game::PIXELS_OFFSET_SPAWN_BOTS < m_camera.x())
        {
            m_health = 0;
        }
    }

    void Bot::resolveCollision(Actor& other)
    {
        // Hit by player's projectile with same color
        if (other.type() == PROJECTILE && getColor() == other.getColor())
        {
            setHit(true);
            takeDamage(DAMAGE_BY_PROJECTILE);
        }

        // Hit by player
        if (other.type() == PLAYER)
        {
            m_health = 0;
        }
    }
    void Bot::play()
    {
        m_explosionSound.play(m_explosionVolume);
    }

    Bot::~Bot()
    {
        if(m_isKilled){
            play();
        }
    }

} /* namespace jumper */
