//
// Created by isaak on 26.11.15.
//

#include "Vector2F.hpp"

namespace jumper
{

Vector2F::Vector2F(float x, float y)
        :	m_x(x), m_y(y)
{
}

Vector2F::Vector2F(const Vector2F& other)
{
    m_x = other.m_x;
    m_y = other.m_y;
}

Vector2F::~Vector2F()
{
    // TODO Auto-generated destructor stub
}

Vector2F Vector2F::operator =(const Vector2F& other)
{
    if(this != &other)
    {
        m_x = other.m_x;
        m_y = other.m_y;
    }
}

Vector2F Vector2F::operator +(const Vector2F& other) const
{
    Vector2F p(*this);
    p += other;
    return p;
}

void Vector2F::operator +=(const Vector2F& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
}

Vector2F Vector2F::operator *(const double& scalar) const
{
    Vector2F p(this->m_x*scalar, this->m_y*scalar);
    return p;
}

void Vector2F::operator *=(const double& scalar)
{
    m_x *= scalar;
    m_y *= scalar;
}

Vector2F Vector2F::operator *(const Vector2F& vec) const
{
    Vector2F p(this->m_x*vec.x(), this->m_y*vec.y());
    return p;
}

void Vector2F::operator *=(const Vector2F& vec)
{
    m_x *= vec.x();
    m_y *= vec.y();
}

float Vector2F::x() const
{
    return m_x;
}

void Vector2F::setX(float x)
{
    m_x = x;
}

float Vector2F::y() const
{
    return m_y;
}

void Vector2F::setY(float y)
{
    m_y = y;
}

} /* namespace jumper */