/**
 * CppWeapon.hpp
 *
 * @date 03.03.16
 * @author Jochen Saalfeld (jsaalfeld@uni-osnabrueck.de)
 */
#ifndef IKARUGA_CPPWEAPON_HPP
#define IKARUGA_CPPWEAPON_HPP

#include <SDL_render.h>
#include "Weapon.hpp"

namespace ikaruga
{
    class CppWeapon : public Weapon
    {
    public:
        /**
         * Creates a weapon
         *
         * @param game Game object where to add the projectiles
         * @param actor From which the projectiles are launched
         * @param projectileTexture Texture for the projectiles
         * @param projectileTextureSize Size of the the texture for the projectiles
         * @param weaponOffset Offset for the weapon from the top left cornor of the player
         * @param projectileColorOffset Offset for the second color in the projectile texture
         * @param coolDown Cool down for the weapon (time between shoots)
         * @param sound String to soundfile
         * @param volume Volume of shoot sound
         * @param collisionDamage Damage of collision
         * @param speed Speed of projectiles launched by this weapon
         * @param numFrames Number of frames for the projectile animation
         */
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

} /* namespace ikaruga */


#endif //IKARUGA_BLASTERWEAPON_HPP
