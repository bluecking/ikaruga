/**
 * LaserWeapon.hpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef JUMPER_LASERWEAPON_HPP
#define JUMPER_LASERWEAPON_HPP

#include <SDL_render.h>
#include "Weapon.hpp"

namespace jumper
{
    /**
     * @brief representation of the weapon Type 'LaserWeapon'
     */
    class LaserWeapon : public Weapon
    {
    public:
        /**
         * Constructor
         *
         * @param game the game
         * @param actor the actor
         * @param projectileTexture projectile texture
         * @param projectileTextureSize projectile texture size
         * @param weaponOffset weapon offset in texture
         * @param projectileColorOffset projectile offset in texture
         * @param coolDown cooldown
         */
        LaserWeapon(Game& game,
                    Actor& actor,
                    SDL_Texture* projectileTexture,
                    const Vector2i& projectileTextureSize,
                    const Vector2f& weaponOffset,
                    const Vector2f& projectileColorOffset,
                    float coolDown);

        /**
         * Shoots a single projectile in a straight line
         *
         * @param direction Direction in which the projectile should move
         * @param spawnPosition Position where the projectiles should spawn
         */
        virtual void shoot(const Vector2f& direction, const Vector2f& spawnPosition);
    };

} /* namespace jumper */


#endif //JUMPER_LASERWEAPON_HPP
