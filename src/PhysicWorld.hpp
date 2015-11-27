//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_PHYSICWORLD_H
#define JUMPER_PHYSICWORLD_H

#include "Vector2F.hpp"

namespace jumper
{
class PhysicWorld
{
public:


    PhysicWorld();
    PhysicWorld(const Vector2F &m_gravity,
                const Vector2F &m_jump,
                const Vector2F &m_move,
                const Vector2F &m_damping,
                double m_maxVelJmp,
                double m_maxVelRun,
                double m_maxVelFall,
                double m_jumpHeight);

    const Vector2F &gravity() const;

    void setGravity(const Vector2F &m_gravity);

    const Vector2F &jumpForce() const;

    void setJumpFore(const Vector2F &m_jump);

    const Vector2F &move() const;

    void setMove(const Vector2F &m_move);

    const Vector2F &damping() const;

    void setDamping(const Vector2F &m_damping);

    double maxJumpVelocity() const;

    void setMaxJumpVelocity(double m_maxVelJmp);

    double maxVelocity() const;

    void setMaxVelocity(double m_maxVelRun);

    double maxFallVelocity() const;

    void setMaxFallVelocity(double m_maxVelFall);

    double jumpHeight() const;

    void setJumpHeight(double m_jumpHeight);

private:
    Vector2F m_gravity;
    Vector2F m_jump;
    Vector2F m_move;
    Vector2F m_damping;
    double m_maxVelJmp;
    double m_maxVelRun;
    double m_maxVelFall;
    double m_jumpHeight;
};

}
#endif //JUMPER_PHYSICWORLD_H
