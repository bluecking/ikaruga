/**
 * Weapon.cpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include "Weapon.hpp"

namespace jumper
{
    Weapon::Weapon(Game& game, Actor& actor)
    : m_game(game), m_actor(actor)
    {

    }

    Weapon::~Weapon()
    {

    }
}
