/*
 * Camera.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "Camera.hpp"

namespace jumper
{



int Camera::x()
{
	return m_position.x();
}

int Camera::y()
{
	return m_position.y();
}

Camera::Camera()
{
	m_position.setX(0);
	m_position.setY(0);
}

void Camera::move(const Vector2i& p)
{
	m_position += p;
}

Camera::Camera(const Vector2i& Vector2i)
	: m_position(Vector2i)
{
}

Vector2i& Camera::position()
{
	return m_position;
}

Camera::~Camera()
{
	// Nothing to do yet
}

} /* namespace jumper */
