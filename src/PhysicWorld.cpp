//
// Created by isaak on 26.11.15.
//

#include "PhysicWorld.hpp"
namespace jumper
{
    PhysicWorld::PhysicWorld() : m_gravity(0,400),
                                 m_move(800,0),
                                 m_jump(-440,0),
                                 m_damping(0.9,1.0),
                                 m_maxVelJmp(300),
                                 m_maxVelRun(120),
                                 m_maxVelFall(250),
                                 m_jumpHeight(90)
    {

    }

    PhysicWorld::PhysicWorld(const Vector2F &m_gravity,
                             const Vector2F &m_jump,
                             const Vector2F &m_move,
                             const Vector2F &m_damping,
                             double m_maxVelJmp,
                             double m_maxVelRun,
                             double m_maxVelFall,
                             double m_jumpHeight)
                            : m_gravity(m_gravity),
                              m_jump(m_jump),
                              m_move(m_move),
                              m_damping(m_damping),
                              m_maxVelJmp(m_maxVelJmp),
                              m_maxVelRun(m_maxVelRun),
                              m_maxVelFall(m_maxVelFall),
                              m_jumpHeight(m_jumpHeight)
    {

    }

    const Vector2F & PhysicWorld::getM_gravity() const
    {
        return m_gravity;
    }

    void PhysicWorld::setM_gravity(const Vector2F &m_gravity)
    {
        PhysicWorld::m_gravity = m_gravity;
    }

    const Vector2F & PhysicWorld::getM_jump() const
    {
        return m_jump;
    }

    void PhysicWorld::setM_jump(const Vector2F &m_jump)
    {
        PhysicWorld::m_jump = m_jump;
    }

    const Vector2F & PhysicWorld::getM_move() const
    {
        return m_move;
    }

    void PhysicWorld::setM_move(const Vector2F &m_move)
    {
        PhysicWorld::m_move = m_move;
    }

    const Vector2F & PhysicWorld::getM_damping() const
    {
        return m_damping;
    }

    void PhysicWorld::setM_damping(const Vector2F &m_damping)
    {
        PhysicWorld::m_damping = m_damping;
    }

    double PhysicWorld::getM_maxVelJmp() const
    {
        return m_maxVelJmp;
    }

    void PhysicWorld::setM_maxVelJmp(double m_maxVelJmp)
    {
        PhysicWorld::m_maxVelJmp = m_maxVelJmp;
    }

    double PhysicWorld::getM_maxVelRun() const
    {
        return m_maxVelRun;
    }

    void PhysicWorld::setM_maxVelRun(double m_maxVelRun)
    {
        PhysicWorld::m_maxVelRun = m_maxVelRun;
    }

    double PhysicWorld::getM_maxVelFall() const
    {
        return m_maxVelFall;
    }

    void PhysicWorld::setM_maxVelFall(double m_maxVelFall)
    {
        PhysicWorld::m_maxVelFall = m_maxVelFall;
    }

    double PhysicWorld::getM_jumpHeight() const
    {
        return m_jumpHeight;
    }

    void PhysicWorld::setM_jumpHeight(double m_jumpHeight)
    {
        PhysicWorld::m_jumpHeight = m_jumpHeight;
    }
}