//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_PHYSICPLAYER_H
#define JUMPER_PHYSICPLAYER_H

#include "Pixel.hpp"
#include "Vector2F.hpp"

namespace jumper
{
class PhysicPlayer
{
public:
    PhysicPlayer();

    PhysicPlayer(const Vector2F &m_pos, const Vector2F &m_acc, const Vector2F &m_vel);

    Vector2F &getM_pos();

    void setM_pos(const Vector2F &m_pos);

    Vector2F &getM_acc();

    void setM_acc(const Vector2F &m_acc);

    Vector2F &getM_vel();

    void setM_vel(const Vector2F &m_vel);

private:
    Vector2F    m_pos;
    Vector2F    m_acc;
    Vector2F    m_vel;

};
}

#endif //JUMPER_PHYSICPLAYER_H
