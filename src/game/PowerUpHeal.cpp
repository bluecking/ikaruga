/**
 * PowerUpHeal.cpp
 *
 *  @date   01.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#include "PowerUpHeal.hpp"

namespace jumper
{
    PowerUpHeal::PowerUpHeal(
            SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
            : PowerUp(renderer, texture, frameWidth, frameHeight, numFrames)
    {
        setType(POWERUP);
    }

    void PowerUpHeal::consume(Player* player)
    {
        player->setHealth(player->getInitial_health());
    }
}
