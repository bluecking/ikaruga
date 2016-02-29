/**
 * CollisionManager.hpp
 *
 *  @date   26.02.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#ifndef SRC_COLLISIONMANAGER_HPP
#define SRC_COLLISIONMANAGER_HPP

#include <vector>
#include "Actor.hpp"

namespace jumper
{
    using std::vector;
    using jumper::Actor;

    class CollisionManager
    {
    public:
        /**
         * Sorts actors vector by their x position and uses sweep and prune algorithm
         * to invoke the resolveCollision method in O(n * log(n)) time complexity.
         *
         * @parameter actors Vector of available actors in the game.
         */
        void checkCollision(vector<Actor*>& actors);
    };

#endif //SRC_COLLISIONMANAGER_HPP
}
