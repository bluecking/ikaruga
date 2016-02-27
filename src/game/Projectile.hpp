/**
 * Projectile.hpp
 * 
 * @date 23.02.16
 * @author Johan M. von Behren (jvonbehren@uni-osnabrueck.de)
 */
#ifndef JUMPER_PROJECTILE_HPP
#define JUMPER_PROJECTILE_HPP

#include "Level.hpp"
#include "Game.hpp"

namespace jumper {
    /**
     * @brief represents the projectile
     */
    class Projectile : public Actor {
    public:
        /**
         * Constructor
         *
         * @param renderer the renderer
         * @param texture the texture of the projectile
         * @param frameWidth the frame width of the projectile
         * @param frameHeight the fram heigth of the projectile
         * @param numFrames the number of frames
         */
        Projectile(SDL_Renderer *renderer, SDL_Texture *texture, int frameWidth, int frameHeight, int numFrames);

        /**
         * Destructor
         */
        virtual ~Projectile();

        /**
         * move to the level
         *
         * @param level the level
         */
        virtual void move(Level &level);

        /**
         * the direction of the projectile
         *
         * @return the direction of the projectile
         */
        const Vector2f &getDirection() const { return m_direction; }

        /**
         * set the direction of the projectile
         *
         * @param m_direction the direction of the projectile
         */
        void setDirection(const Vector2f &m_direction) { Projectile::m_direction = m_direction; }

        /**
         * launch the projectile
         */
        void launch() { m_launched = true; }

    protected:
        //the direction of the projectile
        Vector2f m_direction;

        //true if launched, false if not
        bool m_launched;
    };
}


#endif //JUMPER_PROJECTILE_HPP
