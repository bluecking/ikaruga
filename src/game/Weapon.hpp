/**
 * Weapon.hpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef JUMPER_WEAPON_HPP
#define JUMPER_WEAPON_HPP

#include <SDL_stdinc.h>
#include <SDL_render.h>
#include "Vector.hpp"
#include "Sound.hpp"
using std::string;

namespace jumper
{
    class Game;

    class Actor;

    /**
     * @brief Absract class for weapons. Handles basic functionality like weapon cool down.
     */
    class Weapon
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
         * @param name Name of the weapon
         * @param evolution Evolution Stage of the Weapon
         */
        Weapon(Game& game,
               Actor& actor,
               SDL_Texture* projectileTexture,
               const Vector2i& projectileTextureSize,
               const Vector2f& weaponOffset,
               const Vector2f& projectileColorOffset,
               float coolDown,
               string name,
               int evolution,
               float speed,
               int numFrames);

        virtual ~Weapon();

        /**
         * Creates projectiles and adds them to the game
         *
         * @param direction Direction in which the projectile should move
         * @param spawnPosition Position where the projectiles should spawn
         */
        virtual void shoot(const Vector2f& direction, const Vector2f& spawnPosition) = 0;

        /**
         * Returns the Weapon Name
         *
         * @returns: Weapon Name
         */
        string getWeaponName(void)
        { return m_name;}

        /**
         * Returns the Weapon Evolution Stage
         *
         * @returns: Weapon Evolution Stage
         */
        int getEvolutionStage(void)
        { return m_evolution; }

        // The sound, the Weapon should make
        Sound m_sound;

    protected:
        // Game where to add the projectiles
        Game& m_game;

        // Actor which shoots the projectiles
        Actor& m_actor;

        // Timestamp of the last shoot
        Uint32 m_lastShoot;

        // Cool down for the weapon
        float m_coolDown;

        // Texture for the projectile
        SDL_Texture* m_projectileTexture;

        // Size of the projectile texture
        const Vector2i& m_projectileTextureSize;

        // Offset for the weapon from the top left cornor of the actor
        const Vector2f& m_weaponOffset;

        // Offset for the second color in the projectile texture
        const Vector2f& m_projectileColorOffset;

        /**
         * Checks if the weapon is ready to fire (waits for weapon cool down)
         *
         * @return True if the weapon can be fired, false else
         */
        bool weaponReady();

        //Name of the Weapon
        string m_name;

        //Evlolution Stage of Weapon
        int m_evolution;

        float m_speed;

        int m_numFrames;
    };
} /* namespace jumper */


#endif //JUMPER_WEAPON_HPP
