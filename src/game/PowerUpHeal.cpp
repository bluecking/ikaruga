/**
 * PowerUpHeal.cpp
 *
 *  @date   01.03.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#include "PowerUpHeal.hpp"

namespace jumper {
    PowerUpHeal::PowerUpHeal(
            SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames, int health,
            int collisionDamage) : PowerUp(renderer, texture, frameWidth, frameHeight, numFrames, health, collisionDamage)
    {

    }

    void PowerUpHeal::consume(Player* player)
    {
        player->setHealth(100);
    }
}