/**
 * CollisionManager.cpp
 *
 *  @date   26.02.16
 *  @author Benjamin Lücking <bluecking@uos.de>
 */

#include "CollisionManager.hpp"
#include <algorithm>

bool compareActorXPositions(Actor* first, Actor* second)
{
    return first->position().x() < second->position().x();
}

void CollisionManager::checkCollision(vector<Actor*>& actors)
{
    // O(n*log(n))
    sort(actors.begin(), actors.end(), compareActorXPositions);


    // Sweep and Prune algorithm. Check only actors with actors that have overlapping x positions
    for (auto currentAABB = actors.begin(); currentAABB != actors.end(); ++currentAABB)
    {
        auto otherAABB = currentAABB;

        for (++otherAABB; otherAABB != actors.end(); ++otherAABB)
        {
            SDL_Rect hitBoxA = (*currentAABB)->getHitbox();
            SDL_Rect hitBoxB = (*otherAABB)->getHitbox();

            // Stop testing collision with current actor,
            // if next actor's left boundary is beyond current actor's right boundary
            if ((hitBoxA.x + hitBoxA.w) < hitBoxB.x)
            {
                break;
            }

            SDL_Rect intersection;
            SDL_IntersectRect(&hitBoxA, &hitBoxB, &intersection);

            if (intersection.h > 0 && intersection.w > 0)
            {
                (*currentAABB)->resolveCollision(**otherAABB);
                (*otherAABB)->resolveCollision(**currentAABB);
            }
        }
    }
}
