/**
 * PowerUpGodMode.hpp
 *
 *  @date   02.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#ifndef SCROLLER_POWERUPGODMODE_HPP
#define SCROLLER_POWERUPGODMODE_HPP

#include "PowerUp.hpp"
namespace jumper {
    class PowerUpGodMode final : public PowerUp
    {
    public:
        PowerUpGodMode(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

        /**
         * see PowerUp::consume(Player& player)
         */
        virtual void consume(Player& player);

        /**
         * see PowerUp::stop(Player& player)
         */
        virtual void stop(Player& player);
    };

}


#endif //SCROLLER_POWERUPGODMODE_HPP
