/**
 * PowerUpWeapon.hpp
 * 
 * @date 02.03.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef SCROLLER_POWERUPWEAPON_HPP
#define SCROLLER_POWERUPWEAPON_HPP

#include "PowerUp.hpp"

namespace jumper
{
    class PowerUpWeapon : public PowerUp
    {
    public:
        PowerUpWeapon(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames,
                      Weapon* weapon);

        virtual void consume(Player* player);

    private:
        Weapon* m_weapon;
    };
}

#endif //SCROLLER_POWERUPWEAPON_HPP
