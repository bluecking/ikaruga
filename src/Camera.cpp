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

void Camera::move(const Pixel& p)
{
	m_position += p;
}

Camera::Camera(const Pixel& pixel)
	: m_position(pixel)
{
}

Pixel& Camera::position()
{
	return m_position;
}

Camera::~Camera()
{
	// Nothing to do yet
}

} /* namespace jumper */
