/**
 * PowerUpHeal.hpp
 *
 *  @date   01.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#ifndef SCROLLER_POWERUPHEAL_HPP
#define SCROLLER_POWERUPHEAL_HPP

#include "PowerUp.hpp"

namespace jumper
{
    class PowerUpHeal : public PowerUp
    {

    public:
        PowerUpHeal(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames,
                    int healPercentage);

        /**
         * see PowerUp::consume(Player& player)
         */
        virtual void consume(Player& player);

        /**
         * see PowerUp::stop(Player& player)
         */
        virtual void stop(Player& player);

    private:
        int m_healPercentage;
    };
}


#endif //SCROLLER_POWERUPHEAL_HPP
