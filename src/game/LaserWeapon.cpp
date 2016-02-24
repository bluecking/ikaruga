/**
 * LaserWeapon.cpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#include "LaserWeapon.hpp"
#include "Projectile.hpp"

namespace jumper
{
    void LaserWeapon::shoot(const Vector2f& direction, const Vector2f& spawnPosition)
    {
        Projectile* projectile = new Projectile(m_actor.getRenderer(), m_actor.getTexture(), m_actor.frameWidth(),
                              m_actor.frameHeight(), m_actor.numFrames());

        projectile->setDirection(direction);
        projectile->setPosition(spawnPosition);
        projectile->setColor(m_actor.getColor());
        projectile->launch();

        m_game.addActor(projectile);
    }

    LaserWeapon::LaserWeapon(Game& game, Actor& actor)
            : Weapon(game, actor)
    {

    }
}
