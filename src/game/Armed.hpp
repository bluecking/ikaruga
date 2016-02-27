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
    /**
     * @brief Represents an armed object which has a weapon. With the weapon it's able to shoot projectiles to
     * a configured direction.
     */
    class Armed
    {
    public:
        Armed();

        virtual ~Armed();

        /**
         * Shoots projectiles
         */
        virtual void shoot() = 0;

        void setWeapon(Weapon* weapon)
        { m_weapon = weapon; }

        Weapon* getWeapon(void)
        { return m_weapon; }

    protected:
        // The weapon
        Weapon* m_weapon;
    };
}

#endif //JUMPER_ARMED_HPP
