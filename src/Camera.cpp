/*
 * Camera.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "Camera.hpp"

namespace jumper
{

Camera::Camera(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Camera::moveX(int pixels)
{
	m_x += pixels;
}

void Camera::moveY(int pixels)
{
	m_y += pixels;
}

int Camera::x()
{
	return m_x;
}

int Camera::y()
{
	return m_y;
}

Camera::~Camera()
{
	// Nothing to do yet
}

} /* namespace jumper */
