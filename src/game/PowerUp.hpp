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
        virtual void move(Level& level) final;
        virtual void onCollide() final;
        virtual void resolveCollision(Actor& other) final;

        /**
         * This method will be invoked by the player on every game update, as long as he has not dropped the powerup.
         *
         * @param player The player passes itself, so the powerup can manipulate the player
         */
        virtual void consume(Player& player) = 0;

        /**
         * This method will be invoked by the player as soon as the player drops the powerup.
         *
         * @param player The player passes itself, so the powerup can manipulate the player
         */
        virtual void stop(Player& player) = 0;

        int getExpirationTime() const {
            return m_expirationTime;
        }

        void setExpirationTime(int expirationTime)
        {
            m_expirationTime = expirationTime;
        }

    private:
        int m_expirationTime;
    };
}

#endif //SCROLLER_POWERUP_HPP
