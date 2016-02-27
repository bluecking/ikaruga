/*
 * KillAnimation.hpp
 *
 *  Created on: Feb 21, 2016
 *      Author: twiemann
 */

#ifndef SRC_GAME_KILLANIMATION_HPP_
#define SRC_GAME_KILLANIMATION_HPP_

#include "Item.hpp"

namespace jumper {
    /**
     * @brief represents kill animations
     */
    class KillAnimation : public Item {
    public:
        /**
        * constructor
        *
        * @param actor the actor
        */
        KillAnimation(Actor *actor);


        virtual ~KillAnimation();

        /**
         * renders the kill animation
         */
        virtual void render();

    private:
        //the rotation angle
        float m_rotAngle;

        //the y position
        int m_yPos;

    };

} /* namespace jumper */

#endif /* SRC_GAME_KILLANIMATION_HPP_ */
