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

using std::vector;
using jumper::Actor;

class CollisionManager
{
public:
    void checkCollision(vector<Actor*>& actors);
};

#endif //SRC_COLLISIONMANAGER_HPP
