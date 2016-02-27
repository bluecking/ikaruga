/*
 * Collidable.hpp
 *
 *  Created on: Feb 21, 2016
 *      Author: twiemann
 */

#ifndef SRC_GAME_COLLIDABLE_HPP_
#define SRC_GAME_COLLIDABLE_HPP_

#include "Level.hpp"
#include "Collision.hpp"

namespace jumper {

/**
 * @brief virtual representation of collisions
 */
    class Collidable {
    public:
        /**
         * the standard constructor
         */
        Collidable();

        /**
         * the standard destructor
         */
        virtual ~Collidable();

        /**
         * get the Collission of two collidables
         *
         * @param other the collidable
         * @returns the collision
         */
        virtual Collision getCollision(Collidable &other) = 0;

    protected:

    };

} /* namespace jumper */

#endif /* SRC_GAME_COLLIDABLE_HPP_ */
