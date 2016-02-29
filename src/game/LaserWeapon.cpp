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
        // Ignore shoots when weapon is not ready
        if (!weaponReady())
        {
            return;
        }

        // spawn projectile
        Projectile* projectile = new Projectile(m_actor.getRenderer(), m_projectileTexture, m_projectileTextureSize.x(),
                                                m_projectileTextureSize.y(), 1);

        projectile->setColorOffset(m_projectileColorOffset);
        projectile->setDirection(direction);
        projectile->setType(ActorType::PROJECTILE);
        projectile->setPosition(spawnPosition + m_weaponOffset);
        projectile->setColor(m_actor.getColor());
        projectile->launch();

        if (m_actor.type() == ActorType::ACTOR)
        {
            m_sound.play();
        }

        m_game.addActor(projectile);
    }

    //TODO ~ Set Weapon Name and Evolution Stage and Sound from XML
    LaserWeapon::LaserWeapon(Game& game,
                             Actor& actor,
                             SDL_Texture* projectileTexture,
                             const Vector2i& projectileTextureSize,
                             const Vector2f& weaponOffset,
                             const Vector2f& projectileColorOffset,
                             float coolDown)
            : Weapon(game,
                     actor,
                     projectileTexture,
                     projectileTextureSize,
                     weaponOffset,
                     projectileColorOffset,
                     coolDown,
                     "LaserGun",
                     1)
    {
        m_sound = Sound("/sounds/laser.wav", SoundType::SOUND, *game.getLevel());
    }
}
