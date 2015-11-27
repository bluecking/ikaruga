//
// Created by isaak on 26.11.15.
//

#include "PhysicPlayer.hpp"
namespace jumper
{
    PhysicPlayer::PhysicPlayer() : m_pos(0,0), m_vel(0,0)
    {

    }

    PhysicPlayer::PhysicPlayer(const Vector2F &m_pos, const Vector2F &m_acc, const Vector2F &m_vel) :
            m_pos(m_pos),  m_vel(m_vel)
    {

    }

    Vector2F & PhysicPlayer::getPosition()
    {
        return m_pos;
    }

    void PhysicPlayer::setPosition(const Vector2F &m_pos)
    {
        PhysicPlayer::m_pos = m_pos;
    }


    Vector2F & PhysicPlayer::getVel()
    {
        return m_vel;
    }

    void PhysicPlayer::setVel(const Vector2F &m_vel)
    {
        PhysicPlayer::m_vel = m_vel;
    }
}