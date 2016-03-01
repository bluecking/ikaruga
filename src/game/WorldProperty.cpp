//
// Created by isaak on 26.11.15.
//

#include "WorldProperty.hpp"
namespace jumper
{

WorldProperty::WorldProperty()
	: m_damping(0.95,0.95), m_scrollingSpeed(100, 0)
{

}

WorldProperty::WorldProperty(const Vector2f &damping)
 	 : m_damping(damping)
{

}

const Vector2f& jumper::WorldProperty::damping() const
{
	return m_damping;
}

void jumper::WorldProperty::setDamping(const Vector2f& damping)
{
	m_damping = damping;
}

}
