//
// Created by isaak on 26.11.15.
//

#include <ostream>
#include "Vector2f.hpp"

namespace jumper
{

Vector2f::Vector2f(float x, float y)
        :	m_x(x), m_y(y)
{
}

Vector2f::Vector2f(const Vector2f & other)
{
    m_x = other.m_x;
    m_y = other.m_y;
}

Vector2f::~Vector2f()
{
    // TODO Auto-generated destructor stub
}

Vector2f Vector2f::operator =(const Vector2f & other)
{
    if(this != &other)
    {
        m_x = other.m_x;
        m_y = other.m_y;
    }
}

Vector2f Vector2f::operator +(const Vector2f & other) const
{
    Vector2f p(*this);
    p += other;
    return p;
}

void Vector2f::operator +=(const Vector2f & other)
{
    m_x += other.m_x;
    m_y += other.m_y;
}

Vector2f Vector2f::operator *(const double& scalar) const
{
    Vector2f p(this->m_x * scalar, this->m_y * scalar);
    return p;
}

void Vector2f::operator *=(const double& scalar)
{
    m_x *= scalar;
    m_y *= scalar;
}

Vector2f Vector2f::operator *(const Vector2f & vec) const
{
    Vector2f p(this->m_x * vec.x(), this->m_y * vec.y());
    return p;
}

void Vector2f::operator *=(const Vector2f & vec)
{
    m_x *= vec.x();
    m_y *= vec.y();
}

float Vector2f::x() const
{
    return m_x;
}

void Vector2f::setX(float x)
{
    m_x = x;
}

float Vector2f::y() const
{
    return m_y;
}

void Vector2f::setY(float y)
{
    m_y = y;
}

std::ostream& operator<<(std::ostream& stream, const jumper::Vector2f & vec)
{
    stream << "[" <<vec.x() << "|" << vec.y() << "]" << std::endl;
    return stream;
}

Vector2f Vector2f::operator-(const Vector2f &other) const
{
    Vector2f p(*this);
    p += other;
    return p;
}

void Vector2f::operator-=(const Vector2f &other)
{
    m_x += other.m_x;
    m_y += other.m_y;
}
} /* namespace jumper */