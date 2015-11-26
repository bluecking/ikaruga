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

    const Vector2F &getM_gravity() const;

    void setM_gravity(const Vector2F &m_gravity);

    const Vector2F &getM_jump() const;

    void setM_jump(const Vector2F &m_jump);

    const Vector2F &getM_move() const;

    void setM_move(const Vector2F &m_move);

    const Vector2F &getM_damping() const;

    void setM_damping(const Vector2F &m_damping);

    double getM_maxVelJmp() const;

    void setM_maxVelJmp(double m_maxVelJmp);

    double getM_maxVelRun() const;

    void setM_maxVelRun(double m_maxVelRun);

    double getM_maxVelFall() const;

    void setM_maxVelFall(double m_maxVelFall);

    double getM_jumpHeight() const;

    void setM_jumpHeight(double m_jumpHeight);

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
