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

PhysicWorld::PhysicWorld(const Vector2f &gravity,
		const Vector2f &jump,
		const Vector2f &move,
		const Vector2f &damping,
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

const Vector2f & PhysicWorld::gravity() const
{
	return m_gravity;
}

void PhysicWorld::setGravity(const Vector2f &m_gravity)
{
	PhysicWorld::m_gravity = m_gravity;
}

const Vector2f & PhysicWorld::jumpForce() const
{
	return m_jump;
}

void PhysicWorld::setJumpFore(const Vector2f &m_jump)
{
	PhysicWorld::m_jump = m_jump;
}

const Vector2f & PhysicWorld::move() const
{
	return m_move;
}

void PhysicWorld::setMove(const Vector2f &m_move)
{
	PhysicWorld::m_move = m_move;
}

const Vector2f & PhysicWorld::damping() const
{
	return m_damping;
}

void PhysicWorld::setDamping(const Vector2f &m_damping)
{
	PhysicWorld::m_damping = m_damping;
}

double PhysicWorld::maxJumpVelocity() const
{
	return m_maxVelJmp;
}

void PhysicWorld::setMaxJumpVelocity(double m_maxVelJmp)
{
	PhysicWorld::m_maxVelJmp = m_maxVelJmp;
}

double PhysicWorld::maxVelocity() const
{
	return m_maxVelRun;
}

void PhysicWorld::setMaxVelocity(double m_maxVelRun)
{
	PhysicWorld::m_maxVelRun = m_maxVelRun;
}

double PhysicWorld::maxFallVelocity() const
{
	return m_maxVelFall;
}

void PhysicWorld::setMaxFallVelocity(double m_maxVelFall)
{
	PhysicWorld::m_maxVelFall = m_maxVelFall;
}

double PhysicWorld::jumpHeight() const
{
	return m_jumpHeight;
}

void PhysicWorld::setJumpHeight(double m_jumpHeight)
{
	PhysicWorld::m_jumpHeight = m_jumpHeight;
}
}
