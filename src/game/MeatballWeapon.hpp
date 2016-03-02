/**
 * MeatballWeapon.hpp
 * 
 * @date 02.03.16
 * @author Dennis Altenhoff (daltenhoff@uni-osnabrueck.de)
 */
#ifndef JUMPER_MEATBALLWEAPON_HPP
#define JUMPER_MEATBALLWEAPON_HPP

#include <SDL_render.h>
#include "Weapon.hpp"

namespace jumper
{
    class MeatballWeapon : public Weapon
    {
    public:
        MeatballWeapon(Game& game,
                    Actor& actor,
                    SDL_Texture* projectileTexture,
                    const Vector2i& projectileTextureSize,
                    const Vector2f& weaponOffset,
                    const Vector2f& projectileColorOffset,
                    float coolDown,
                    std::string sound,
                    int volume,
                    int collisionDamage,
                    float speed,
                    int numFrames);

        /**
         * Shoots a single projectile in a straight line
         *
         * @param direction Direction in which the projectile should move
         * @param spawnPosition Position where the projectiles should spawn
         */
        virtual void shoot(const Vector2f& direction, const Vector2f& spawnPosition);

        int m_volume;

        int m_collisionDamage;

    };

} /* namespace jumper */


#endif //JUMPER_MEATBALLWEAPON_HPP
