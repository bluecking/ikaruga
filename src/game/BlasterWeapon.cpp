/**
 * BlasterWeapon.cpp
 * 
 * @date 02.03.16
 * @author Dennis Altenhoff (daltenhoff@uni-osnabrueck.de)
 */
#include "BlasterWeapon.hpp"
#include "Projectile.hpp"

namespace jumper
{
    void BlasterWeapon::shoot(const Vector2f& direction, const Vector2f& spawnPosition)
    {
        // Ignore shoots when weapon is not ready
        if (!weaponReady())
        {
            return;
        }

        // spawn projectile
        Projectile* projectile = new Projectile(m_actor.getRenderer(),
                                                m_projectileTexture,
                                                m_projectileTextureSize.x(),
                                                m_projectileTextureSize.y(),
                                                m_numFrames,
                                                m_collisionDamage,
                                                m_speed);

        projectile->setColorOffset(m_projectileColorOffset);
        projectile->setDirection(direction);
        projectile->setType(ActorType::PROJECTILE);
        projectile->setPosition(spawnPosition + m_weaponOffset);
        projectile->setColor(m_actor.getColor());
        projectile->setOriginActor(&m_actor);
        projectile->launch();

        if (m_actor.type() == ActorType::PLAYER)
        {
            m_sound.play(m_volume,this->m_coolDown*1000);
        }

        m_game.addActor(projectile);
    }

    //TODO ~ Set Weapon Name and Evolution Stage and Sound from XML
    BlasterWeapon::BlasterWeapon(Game& game,
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
                             int numFrames)
            : Weapon(game,
                     actor,
                     projectileTexture,
                     projectileTextureSize,
                     weaponOffset,
                     projectileColorOffset,
                     coolDown,
                     "Blaster",
                     1,
                     speed,
                     numFrames)
    {
        m_collisionDamage = collisionDamage;
        m_sound = Sound(sound, SoundType::SOUND);
        m_volume = volume;
    }
}
