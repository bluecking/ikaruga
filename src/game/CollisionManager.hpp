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

namespace ikaruga
{
    using std::vector;

    class CollisionManager
    {
    public:
        /**
         * Sorts actors vector by their x position and uses sweep and prune algorithm
         * to invoke the onActorCollision method in O(n * log(n)) time complexity.
         *
         * @parameter actors Vector of available actors in the game.
         */
        static void checkActorCollision(vector<Actor*>& actors);
    };

#endif //SRC_COLLISIONMANAGER_HPP
}
