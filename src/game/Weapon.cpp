/**
 * Weapon.cpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include <SDL_timer.h>
#include "Weapon.hpp"

namespace jumper
{
    Weapon::Weapon(Game& game, Actor& actor, SDL_Texture* projectileTexture, const Vector2i& projectileTextureSize,
                   const Vector2f& weaponOffset, const Vector2f& projectileColorOffset, float coolDown)
            : m_game(game), m_actor(actor), m_lastShoot(0), m_coolDown(coolDown),
              m_projectileTexture(projectileTexture),
              m_projectileTextureSize(projectileTextureSize), m_weaponOffset(weaponOffset),
              m_projectileColorOffset(projectileColorOffset)
    {

    }

    Weapon::~Weapon()
    {

    }

    bool Weapon::weaponReady()
    {
        if (m_lastShoot == 0)
        {
            m_lastShoot = SDL_GetTicks();
            return true;
        }

        Uint32 ticks = SDL_GetTicks();
        float time = (ticks - m_lastShoot) / 1000.0f;
        if (time > m_coolDown)
        {
            m_lastShoot = ticks;
            return true;
        }

        return false;
    }
}
