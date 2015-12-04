/*
 * Pixel.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: twiemann
 */


#include "Pixel.hpp"

namespace jumper
{

Pixel::Pixel(int x, int y)
	:	m_x(x), m_y(y)
{
}

Pixel::Pixel(const Pixel& other)
{
	m_x = other.m_x;
	m_y = other.m_y;
}

Pixel::~Pixel()
{
	// TODO Auto-generated destructor stub
}

Pixel& Pixel::operator =(const Pixel& other)
{
	if(this != &other)
	{
		m_x = other.m_x;
		m_y = other.m_y;
	}
	return *this;
}

Pixel Pixel::operator +(const Pixel& other) const
{
	Pixel p(*this);
	p += other;
	return p;
}

void Pixel::operator +=(const Pixel& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
}

int Pixel::x() const
{
	return m_x;
}

void Pixel::setX(int x)
{
	m_x = x;
}

int Pixel::y() const
{
	return m_y;
}

void Pixel::setY(int y)
{
	m_y = y;
}

std::ostream& operator<<(std::ostream& stream, const jumper::Pixel& vec)
{
	stream << "[" <<vec.x() << "|" << vec.y() << "]";
	return stream;
}


} /* namespace jumper */
