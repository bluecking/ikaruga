/**
 * PowerUpWeapon.cpp
 * 
 * @date 02.03.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include "PowerUpWeapon.hpp"

namespace jumper
{
    PowerUpWeapon::PowerUpWeapon(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight,
                                 int numFrames, Weapon* weapon)
    : PowerUp(renderer, texture, frameWidth, frameHeight, numFrames), m_weapon(weapon)
    {

    }

    void PowerUpWeapon::consume(Player* player)
    {
        // todo update weapon level if same weapon is consumed again and destroy (delte) old weapon
        m_weapon->setActor(player);
        player->setWeapon(m_weapon);
    }
}
