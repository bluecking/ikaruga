//
// Created by isaak on 26.11.15.
//

#include "PhysicWorld.hpp"
namespace jumper
{
    PhysicWorld::PhysicWorld() : m_gravity(0,400),
                                 m_jump(0,-440),
                                 m_move(800,0),
                                 m_damping(0.9,1.0),
                                 m_maxVelJmp(300),
                                 m_maxVelRun(120),
                                 m_maxVelFall(250),
                                 m_jumpHeight(90)
    {

    }

    PhysicWorld::PhysicWorld(const Vector2F &gravity,
                             const Vector2F &jump,
                             const Vector2F &move,
                             const Vector2F &damping,
                             double maxVelJmp,
                             double maxVelRun,
                             double maxVelFall,
                             double jumpHeight)
                            : m_gravity(gravity),
                              m_jump(jump),
                              m_move(move),
                              m_damping(damping),
                              m_maxVelJmp(maxVelJmp),
                              m_maxVelRun(maxVelRun),
                              m_maxVelFall(maxVelFall),
                              m_jumpHeight(jumpHeight)
    {

    }

    const Vector2F & PhysicWorld::getGravity() const
    {
        return m_gravity;
    }

    void PhysicWorld::setGravity(const Vector2F &m_gravity)
    {
        PhysicWorld::m_gravity = m_gravity;
    }

    const Vector2F & PhysicWorld::getJump() const
    {
        return m_jump;
    }

    void PhysicWorld::setJump(const Vector2F &m_jump)
    {
        PhysicWorld::m_jump = m_jump;
    }

    const Vector2F & PhysicWorld::getMove() const
    {
        return m_move;
    }

    void PhysicWorld::setMove(const Vector2F &m_move)
    {
        PhysicWorld::m_move = m_move;
    }

    const Vector2F & PhysicWorld::getDamping() const
    {
        return m_damping;
    }

    void PhysicWorld::setDamping(const Vector2F &m_damping)
    {
        PhysicWorld::m_damping = m_damping;
    }

    double PhysicWorld::getMaxVelJmp() const
    {
        return m_maxVelJmp;
    }

    void PhysicWorld::setMaxVelJmp(double m_maxVelJmp)
    {
        PhysicWorld::m_maxVelJmp = m_maxVelJmp;
    }

    double PhysicWorld::getMaxVelRun() const
    {
        return m_maxVelRun;
    }

    void PhysicWorld::setMaxVelRun(double m_maxVelRun)
    {
        PhysicWorld::m_maxVelRun = m_maxVelRun;
    }

    double PhysicWorld::getMaxVelFall() const
    {
        return m_maxVelFall;
    }

    void PhysicWorld::setMaxVelFall(double m_maxVelFall)
    {
        PhysicWorld::m_maxVelFall = m_maxVelFall;
    }

    double PhysicWorld::getJumpHeight() const
    {
        return m_jumpHeight;
    }

    void PhysicWorld::setJumpHeight(double m_jumpHeight)
    {
        PhysicWorld::m_jumpHeight = m_jumpHeight;
    }
}