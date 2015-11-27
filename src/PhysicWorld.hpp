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

    const Vector2F &getGravity() const;

    void setGravity(const Vector2F &m_gravity);

    const Vector2F &getJump() const;

    void setJump(const Vector2F &m_jump);

    const Vector2F &getMove() const;

    void setMove(const Vector2F &m_move);

    const Vector2F &getDamping() const;

    void setDamping(const Vector2F &m_damping);

    double getMaxVelJmp() const;

    void setMaxVelJmp(double m_maxVelJmp);

    double getMaxVelRun() const;

    void setMaxVelRun(double m_maxVelRun);

    double getMaxVelFall() const;

    void setMaxVelFall(double m_maxVelFall);

    double getJumpHeight() const;

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
