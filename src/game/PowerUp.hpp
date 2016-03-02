/**
 * PowerUp.hpp
 *
 *  @date   01.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#ifndef SCROLLER_POWERUP_HPP
#define SCROLLER_POWERUP_HPP

#include "Actor.hpp"
#include "Player.hpp"

namespace jumper {

    class Player;

    class PowerUp : public Actor
    {
    public:
        PowerUp(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

        ~PowerUp();
        virtual void move(Level& level);
        virtual void onCollide();
        virtual void resolveCollision(Actor& other);

        virtual void consume(Player* player) = 0;
        int getExpirationTime();
    private:
        int m_expirationTime;
    };
}

#endif //SCROLLER_POWERUP_HPP
