/*
 * Item.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: twiemann
 */

#include "Item.hpp"

namespace jumper {
    Item::Item(SDL_Renderer *renderer,
               SDL_Texture *texture,
               int frameWidth,
               int frameHeight,
               int numFrames,
               int health,
               int collisionDamage)
            : Actor(renderer, texture, frameWidth, frameHeight, numFrames, health, collisionDamage) {
    }

    void Item::move(Level &level) {
        nextFrame();
    }

    Item::~Item() {
        // TODO Auto-generated destructor stub
    }

    void Item::resolveCollision(Actor &other) {

    }
} // namespace jumper
