//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_VECTOR2F_H
#define JUMPER_VECTOR2F_H


namespace jumper
{

/***
 * A class to represent a Vector2F
 */
class Vector2F
{
public:

    /**
     * Constructor
     * @param x		x position of the Vector2F
     * @param y		y position of the Vector2F
     */
    Vector2F(float x = 0, float y = 0);

    /***
     * Copy constructor
     *
     * @param other	The Vector2F that is copied
     */
    Vector2F(const Vector2F& other);

    /***
     * Destructor
     */
    virtual ~Vector2F();

    /***
     * Assignment operator
     *
     * @param other	The Vector2F that is copied into this Vector2F
     * @return		The modified instance.
     */
    Vector2F operator=(const Vector2F& other);

    /***
     * Adds an offset encoded in the other Vector2F
     *
     * @param other	A Vector2F offset added to the current position
     * @return		A modified Vector2F
     */
    Vector2F operator+(const Vector2F& other) const;

    /***
     * Adds an offset encoded in the other Vector2F
     *
     * @param other	A Vector2F offset added to the current position
     */
    void operator+=(const Vector2F& other);

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

private:

    /// x coordinate of the Vector2F
    float m_x;

    /// y coordinate of the Vector2F
    float m_y;
};


} /* namespace jumper */

#endif /* SRC_Vector2F_HPP_ */
