/**
 * Weapon.hpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef JUMPER_WEAPON_HPP
#define JUMPER_WEAPON_HPP

#include "Vector.hpp"

namespace jumper
{
    class Weapon
    {
    public:
        Weapon();
        virtual ~Weapon();
        virtual void shoot(const Vector2f& direction, const Vector2f& spawnPosition) = 0;
    };
} /* namespace jumper */


#endif //JUMPER_WEAPON_HPP
