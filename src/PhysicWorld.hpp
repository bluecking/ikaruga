//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_PHYSICWORLD_H
#define JUMPER_PHYSICWORLD_H

#include "Vector2f.hpp"

namespace jumper
{
class PhysicWorld
{
public:


    PhysicWorld();
    PhysicWorld(const Vector2f &m_gravity,
                const Vector2f &m_jump,
                const Vector2f &m_move,
                const Vector2f &m_damping,
                double m_maxVelJmp,
                double m_maxVelRun,
                double m_maxVelFall,
                double m_jumpHeight);

    const Vector2f &gravity() const;

    void setGravity(const Vector2f &m_gravity);

    const Vector2f &jumpForce() const;

    void setJumpFore(const Vector2f &m_jump);

    const Vector2f &move() const;

    void setMove(const Vector2f &m_move);

    const Vector2f &damping() const;

    void setDamping(const Vector2f &m_damping);

    double maxJumpVelocity() const;

    void setMaxJumpVelocity(double m_maxVelJmp);

    double maxVelocity() const;

    void setMaxVelocity(double m_maxVelRun);

    double maxFallVelocity() const;

    void setMaxFallVelocity(double m_maxVelFall);

    double jumpHeight() const;

    void setJumpHeight(double m_jumpHeight);

private:
    Vector2f m_gravity;
    Vector2f m_jump;
    Vector2f m_move;
    Vector2f m_damping;
    double m_maxVelJmp;
    double m_maxVelRun;
    double m_maxVelFall;
    double m_jumpHeight;
};

}
#endif //JUMPER_PHYSICWORLD_H
