//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_PHYSICPLAYER_H
#define JUMPER_PHYSICPLAYER_H

#include "Vector.hpp"

namespace jumper
{
class PhysicPlayer
{
public:

    PhysicPlayer();

    PhysicPlayer(const Vector2f &m_pos, const Vector2f &m_acc, const Vector2f &m_vel);

    Vector2f &position();

    void setPosition(const Vector2f &m_pos);

    Vector2f &velocity();

    void setVelocity(const Vector2f &m_vel);


private:
    Vector2f m_pos;
    Vector2f m_vel;

};
}

#endif //JUMPER_PHYSICPLAYER_H
