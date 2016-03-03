/**
 * RocketWeapon.hpp
 * 
 * @date 01.03.16
 * @author Dennis Altenhoff (daltenhoff@uni-osnabrueck.de)
 */
#ifndef JUMPER_ROCKETWEAPON_HPP
#define JUMPER_ROCKETWEAPON_HPP

#include <SDL_render.h>
#include "Weapon.hpp"

namespace jumper
{
    class RocketWeapon : public Weapon
    {
    public:
        RocketWeapon(Game& game,
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


#endif //JUMPER_ROCKETWEAPON_HPP
