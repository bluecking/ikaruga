//
// Created by isaak on 26.11.15.
//

#include "WorldProperties.hpp"
namespace jumper
{

WorldProperties::WorldProperties() : m_gravity(0,400),
		m_jump(0,-440),
		m_move(800,0),
		m_damping(0.9,1.0),
		m_maxVelJmp(300),
		m_maxVelRun(120),
		m_maxVelFall(250),
		m_jumpHeight(90)
{

}

WorldProperties::WorldProperties(const Vector2f &gravity,
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

const Vector2f & WorldProperties::gravity() const
{
	return m_gravity;
}

void WorldProperties::setGravity(const Vector2f &m_gravity)
{
	WorldProperties::m_gravity = m_gravity;
}

const Vector2f & WorldProperties::jumpForce() const
{
	return m_jump;
}

void WorldProperties::setJumpFore(const Vector2f &m_jump)
{
	WorldProperties::m_jump = m_jump;
}

const Vector2f & WorldProperties::move() const
{
	return m_move;
}

void WorldProperties::setMove(const Vector2f &m_move)
{
	WorldProperties::m_move = m_move;
}

const Vector2f & WorldProperties::damping() const
{
	return m_damping;
}

void WorldProperties::setDamping(const Vector2f &m_damping)
{
	WorldProperties::m_damping = m_damping;
}

double WorldProperties::maxJumpVelocity() const
{
	return m_maxVelJmp;
}

void WorldProperties::setMaxJumpVelocity(double m_maxVelJmp)
{
	WorldProperties::m_maxVelJmp = m_maxVelJmp;
}

double WorldProperties::maxVelocity() const
{
	return m_maxVelRun;
}

void WorldProperties::setMaxVelocity(double m_maxVelRun)
{
	WorldProperties::m_maxVelRun = m_maxVelRun;
}

double WorldProperties::maxFallVelocity() const
{
	return m_maxVelFall;
}

void WorldProperties::setMaxFallVelocity(double m_maxVelFall)
{
	WorldProperties::m_maxVelFall = m_maxVelFall;
}

double WorldProperties::jumpHeight() const
{
	return m_jumpHeight;
}

void WorldProperties::setJumpHeight(double m_jumpHeight)
{
	WorldProperties::m_jumpHeight = m_jumpHeight;
}
}
