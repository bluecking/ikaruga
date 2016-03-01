/**
 * PowerUp.cpp
 *
 *  @date   01.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#include "PowerUp.hpp"

namespace jumper {
    PowerUp::PowerUp(SDL_Renderer* renderer,
            SDL_Texture* texture,
            int frameWidth,
            int frameHeight,
            int numFrames) : Actor(renderer, texture, frameWidth, frameHeight, numFrames, 1, 0),
                                   m_expirationTime(0)
    {

    }

    void PowerUp::resolveCollision(Actor& other)
    {
        setHealth(0);
    }

    void PowerUp::move(Level& level)
    {
        // DO NOT MOVE AT ALL
    }

    void PowerUp::onCollide()
    {
        // DOES NOT HAPPEN
    }

    PowerUp::~PowerUp()
    {

    }

    int PowerUp::getExpirationTime()
    {
        return m_expirationTime;
    }
}