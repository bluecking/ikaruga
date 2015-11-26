//
// Created by isaak on 26.11.15.
//

#include "PhysicPlayer.hpp"
namespace jumper
{
    PhysicPlayer::PhysicPlayer() : m_pos(0,0), m_acc(0,0), m_vel(0,0)
    {

    }

    PhysicPlayer::PhysicPlayer(const Vector2F &m_pos, const Vector2F &m_acc, const Vector2F &m_vel) :
            m_pos(m_pos), m_acc(m_acc), m_vel(m_vel)
    {

    }

    Vector2F & PhysicPlayer::getM_pos()
    {
        return m_pos;
    }

    void PhysicPlayer::setM_pos(const Vector2F &m_pos)
    {
        PhysicPlayer::m_pos = m_pos;
    }

    Vector2F & PhysicPlayer::getM_acc()
    {
        return m_acc;
    }

    void PhysicPlayer::setM_acc(const Vector2F &m_acc)
    {
        PhysicPlayer::m_acc = m_acc;
    }

    Vector2F & PhysicPlayer::getM_vel()
    {
        return m_vel;
    }

    void PhysicPlayer::setM_vel(const Vector2F &m_vel)
    {
        PhysicPlayer::m_vel = m_vel;
    }
}