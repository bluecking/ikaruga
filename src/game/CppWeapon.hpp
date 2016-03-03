/**
 * CppWeapon.hpp
 *
 * @date 03.03.16
 * @author Jochen Saalfeld (jsaalfeld@uni-osnabrueck.de)
 */
#ifndef JUMPER_CPPWEAPON_HPP
#define JUMPER_CPPWEAPON_HPP

#include <SDL_render.h>
#include "Weapon.hpp"

namespace jumper
{
    class CppWeapon : public Weapon
    {
    public:
        CppWeapon(Game& game,
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


#endif //JUMPER_BLASTERWEAPON_HPP
