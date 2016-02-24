/**
 * Armed.hpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef JUMPER_ARMED_HPP
#define JUMPER_ARMED_HPP

#include "Weapon.hpp"

namespace jumper
{
    class Armed
    {
    public:
        Armed();
        virtual ~Armed();

        virtual void shoot() = 0;

        void setWeapon(Weapon* weapon)
        { m_weapon = weapon; }

    protected:
        Weapon* m_weapon;
    };
}

#endif //JUMPER_ARMED_HPP
