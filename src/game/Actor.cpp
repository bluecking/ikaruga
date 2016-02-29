/*
 * Actor.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#include <SDL.h>
#include <iostream>
#include "Actor.hpp"

using std::cout;
using std::endl;

namespace jumper
{
    Actor::Actor(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
            : AnimatedRenderable(renderer, texture, frameWidth, frameHeight, numFrames), m_color(ColorMode::BLACK)
    {
        m_focus = false;
        m_physicalProps.setPosition(Vector2f(100, 0));
        m_startTicks = 0;
        m_type = PLAYER;

        m_hitbox.w = (int) std::floor(frameWidth * HITBOXFACTOR);
        m_hitbox.h = (int) std::floor(frameHeight * HITBOXFACTOR);

        //TODO: this should not be hardcoded
        m_health = 100;

        m_spawnTime = SDL_GetTicks();
    }

    void Actor::setPhysics(PlayerProperty p)
    {
        m_physicalProps = p;
    }

    Actor::~Actor()
    {

    }

    float Actor::getElapsedTime()
    {
        if (m_startTicks == 0)
        {
            m_startTicks = SDL_GetTicks();
        }

        Uint32 ticks = SDL_GetTicks();
        float time = (ticks - m_startTicks) / 1000.0;
        m_startTicks = ticks;
        return time;
    }

    float Actor::getLiveTime()
    {
        Uint32 ticks = SDL_GetTicks();
        float time = (ticks - m_spawnTime) / 1000.0;
        return time;
    }

    void Actor::render()
    {
        SDL_Rect target;

        target.x = (int) floor(m_physicalProps.position().x() - m_camera.x());
        target.y = (int) floor(m_physicalProps.position().y() - m_camera.y());
        target.w = m_frameWidth;
        target.h = m_frameHeight;

        // Do not render if actor is outside frustrum
        if (target.x + target.w > 0 && target.x + target.w < m_camera.w())
        {
            // Render current animation frame
            SDL_Rect source = m_sourceRect;

            // switch color
            if (m_color == ColorMode::WHITE)
            {
                source.x = source.x + (int) m_colorOffset.x();
                source.y = source.y + (int) m_colorOffset.y();
            }

            // Make the texture opaque
            if (m_hit)
            {
                SDL_SetTextureAlphaMod(m_texture, OPACITY_LEVEL_WHEN_HIT);
                SDL_RenderCopyEx(getRenderer(), m_texture, &source, &target, 0, NULL, SDL_FLIP_NONE);
                SDL_SetTextureAlphaMod(m_texture, 255);
            }
            else
            {
                SDL_RenderCopyEx(getRenderer(), m_texture, &source, &target, 0, NULL, SDL_FLIP_NONE);
            }

//            renderHitbox();
        }

    }

    SDL_Rect& Actor::getHitbox()
    {
        m_hitbox.x = (int) (std::floor((m_frameWidth - m_hitbox.w) / 2) + position().x());
        m_hitbox.y = (int) (std::floor((m_frameHeight - m_hitbox.h) / 2) + position().y());

        return m_hitbox;
    }

    void Actor::setPosition(Vector2f pos)
    {
        m_physicalProps.position() = pos;
    }

    PlayerProperty& Actor::physics()
    {
        return m_physicalProps;
    }

    Vector2f Actor::position()
    {
        return m_physicalProps.position();
    }

    void Actor::resolveCollision(Actor& other)
    {

    }

    Collision Actor::getCollision(Actor& other)
    {
        Collision c;

        // Check for collision
        Vector2f v = m_physicalProps.velocity();

        SDL_Rect myRect;
        myRect.x = position().x();
        myRect.y = position().y();
        myRect.w = w();
        myRect.h = h();

        SDL_Rect otherRect;
        otherRect.x = other.position().x();
        otherRect.y = other.position().y();
        otherRect.w = other.w();
        otherRect.h = other.h();

        SDL_Rect intersection;
        SDL_IntersectRect(&myRect, &otherRect, &intersection);

        if (std::abs(intersection.w) < otherRect.w && intersection.h > 0)
        {
            if (v.y() > 0)
            {
                if (intersection.h < otherRect.h / 2)
                {
                    c.setType(DOWN);
                }
                else
                {
                    c.setType(BOOM);
                }
            }
            else
            {
                if (intersection.h < otherRect.h / 2)
                {
                    c.setType(UP);
                }
                else
                {
                    c.setType(BOOM);
                }
            }
        }

        return c;
    }

    void jumper::Actor::setFocus(bool focus)
    {
        m_focus = focus;
    }

    bool jumper::Actor::hasFocus()
    {
        return m_focus;
    }

    void Actor::toggleColor()
    {
        m_color = m_color == ColorMode::BLACK ? ColorMode::WHITE : ColorMode::BLACK;

    }

    bool Actor::visible()
    {
        SDL_Rect myRect;
        myRect.x = (int) position().x();
        myRect.y = (int) position().y();
        myRect.w = w();
        myRect.h = h();

        SDL_Rect otherRect;
        otherRect.x = (int) m_camera.x();
        otherRect.y = (int) m_camera.y();
        otherRect.w = m_camera.w();
        otherRect.h = m_camera.h();

        SDL_Rect intersection;
        SDL_IntersectRect(&myRect, &otherRect, &intersection);

        return intersection.w > 0 && intersection.h > 0;
    }

    int Actor::getHealth()
    {
        return m_health;
    }

    void Actor::takeDamage(int damage)
    {
        m_health -= damage;
    }

    void Actor::renderHitbox()
    {
        SDL_Rect& hitbox = getHitbox();
        hitbox.x -= m_camera.x();
        hitbox.y -= m_camera.y();

        // Color hitbox depending on the current color state
        if (m_color == ColorMode::BLACK)
        {
            SDL_SetRenderDrawColor(getRenderer(), 255, 0, 0, 0);
        }
        else
        {
            SDL_SetRenderDrawColor(getRenderer(), 0, 255, 0, 0);
        }

        SDL_RenderDrawRect(getRenderer(), &hitbox);
    }

    const bool& Actor::is_hit() const
    {
        return m_hit;
    }
} /* namespace jumper */

