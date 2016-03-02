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
    class LaserWeapon : public Weapon
    {
    public:
        LaserWeapon(Game& game,
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

    };

} /* namespace jumper */


#endif //JUMPER_LASERWEAPON_HPP
