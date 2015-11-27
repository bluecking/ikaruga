//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_VECTOR2F_H
#define JUMPER_VECTOR2F_H


#include <iosfwd>

namespace jumper
{

/***
 * A class to represent a Vector2f
 */
class Vector2f
{
public:

    /**
     * Constructor
     * @param x		x position of the Vector2f
     * @param y		y position of the Vector2f
     */
    Vector2f(float x = 0, float y = 0);

    /***
     * Copy constructor
     *
     * @param other	The Vector2f that is copied
     */
    Vector2f(const Vector2f & other);

    /***
     * Destructor
     */
    virtual ~Vector2f();

    /***
     * Assignment operator
     *
     * @param other	The Vector2f that is copied into this Vector2f
     * @return		The modified instance.
     */
    Vector2f operator=(const Vector2f & other);

    /***
     * Adds an offset encoded in the other Vector2f
     *
     * @param other	A Vector2f offset added to the current position
     * @return		A modified Vector2f
     */
    Vector2f operator+(const Vector2f & other) const;

    /***
     * Adds an offset encoded in the other Vector2f
     *
     * @param other	A Vector2f offset added to the current position
     */
    void operator+=(const Vector2f & other);

    /***
  * Adds an offset encoded in the other Vector2f
  *
  * @param other	A Vector2f offset added to the current position
  * @return		A modified Vector2f
  */
    Vector2f operator-(const Vector2f & other) const;

    /***
     * Adds an offset encoded in the other Vector2f
     *
     * @param other	A Vector2f offset added to the current position
     */
    void operator-=(const Vector2f & other);


    /***
    * Scales the Vector2f
    *
    * @param other	A float with which the Vector should be multiplied
    * @return		A modified Vector2f
    */
    Vector2f operator*(const double& other) const;

    /***
     *
     * @param scalar with which to multiply
     */
    void operator*=(const double& other);

    /***
    * Scales the Vector2f
    *
    * @param other	A float with which the Vector should be multiplied
    * @return		A modified Vector2f
    */
    Vector2f operator*(const Vector2f & other) const;

    /***
     *
     * @param scalar with which to multiply
     */
    void operator*=(const Vector2f & other);

    /// Returns the current x value
    float x() const;

    /***
     * Sets a new x value
     *
     * @param x		A new x value
     */
    void setX(float x);

    /// Returns the current y value
    float y() const;

    /***
     * Sets a new y value
     *
     * @param y 	A new y value
     */
    void setY(float y);

    friend std::ostream& operator<< (std::ostream& stream, const jumper::Vector2f & vec);

private:

    /// x coordinate of the Vector2f
    float m_x;

    /// y coordinate of the Vector2f
    float m_y;
};


} /* namespace jumper */

#endif /* SRC_Vector2F_HPP_ */
