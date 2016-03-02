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

        // Number of projectiles
        int numProjectiles = getEvolutionStage();

        // Scale of spread of projectiles growing with projectile height
        float spreadScale = m_projectileTextureSize.y() * 0.005f;

        // Spawn position of projectiles
        Vector2f spawnPos = (spawnPosition + m_weaponOffset);

        // yOffset for even projectile number
        float yOffset = -(((numProjectiles + 1) % 2) * 0.5f);

        // Pointer for created projectiles
        Projectile* projectile;

        for(int i = 0; i < numProjectiles; i++)
        {
            // Create new projectile
            projectile = new Projectile(m_actor.getRenderer(),
                                        m_projectileTexture,
                                        m_projectileTextureSize.x(),
                                        m_projectileTextureSize.y(),
                                        1,
                                        m_collisionDamage);

            // Calculate y-movement of current projectile
            float moveY = ((numProjectiles / 2) - i + yOffset) * spreadScale;

            // Set projectile properties
            projectile->setColorOffset(m_projectileColorOffset);
            projectile->setDirection(Vector2f(direction.x() * 0.3f, moveY * 0.3f));
            projectile->setType(ActorType::PROJECTILE);
            projectile->setPosition(spawnPos);
            projectile->setColor(m_actor.getColor());
            projectile->setOriginActor(&m_actor);
            projectile->launch();

            // Add created projectile to actors
            m_game.addActor(projectile);
        }

        if (m_actor.type() == ActorType::PLAYER)
        {
            m_sound.play(m_volume, this->m_coolDown * 1000);
        }
    }

    //TODO ~ Set Weapon Name and Evolution Stage and Sound from XML
    LaserWeapon::LaserWeapon(Game& game,
                             Actor& actor,
                             SDL_Texture* projectileTexture,
                             const Vector2i& projectileTextureSize,
                             const Vector2f& weaponOffset,
                             const Vector2f& projectileColorOffset,
                             float coolDown,
                             std::string sound,
                             int volume,
                             int collisionDamage)
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
        m_collisionDamage = collisionDamage;
        m_sound = Sound(sound, SoundType::SOUND);
        m_volume = volume;
    }
}
