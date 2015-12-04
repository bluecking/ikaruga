//
// Created by isaak on 26.11.15.
//

#include "PlayerProperites.hpp"
namespace jumper
{

PlayerProperties::PlayerProperties() : m_pos(0,0), m_vel(0,0)
{

}

PlayerProperties::PlayerProperties(const Vector2f &m_pos, const Vector2f &m_acc, const Vector2f &m_vel) :
            		m_pos(m_pos),  m_vel(m_vel)
{

}

Vector2f& PlayerProperties::position()
{
	return m_pos;
}

void PlayerProperties::setPosition(const Vector2f &m_pos)
{
	PlayerProperties::m_pos = m_pos;
}


Vector2f& PlayerProperties::velocity()
{
	return m_vel;
}

void PlayerProperties::setVelocity(const Vector2f &m_vel)
{
	PlayerProperties::m_vel = m_vel;
}

}
