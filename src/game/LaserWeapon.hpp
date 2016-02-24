/**
 * LaserWeapon.hpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef JUMPER_LASERWEAPON_HPP
#define JUMPER_LASERWEAPON_HPP

#include "Weapon.hpp"

namespace jumper
{
    class LaserWeapon : public Weapon
    {
    public:
        LaserWeapon(Game* game, Actor* actor);
        virtual void shoot(const Vector2f& direction, const Vector2f& spawnPosition);
    };
} /* namespace jumper */


#endif //JUMPER_LASERWEAPON_HPP
