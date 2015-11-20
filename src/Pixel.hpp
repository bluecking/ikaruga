/*
 * Pixel.hpp
 *
 *  Created on: Nov 20, 2015
 *      Author: twiemann
 */

#ifndef SRC_PIXEL_HPP_
#define SRC_PIXEL_HPP_

namespace jumper
{

/***
 * A class to represent a pixel
 */
class Pixel
{
public:

	/**
	 * Constructor
	 * @param x		x position of the pixel
	 * @param y		y position of the pixel
	 */
	Pixel(int x = 0, int y = 0);

	/***
	 * Copy constructor
	 *
	 * @param other	The pixel that is copied
	 */
	Pixel(const Pixel& other);

	/***
	 * Destructor
	 */
	virtual ~Pixel();

	/***
	 * Assignment operator
	 *
	 * @param other	The pixel that is copied into this pixel
	 * @return		The modified instance.
	 */
	Pixel operator=(const Pixel& other);

	/***
	 * Adds an offset encoded in the other pixel
	 *
	 * @param other	A pixel offset added to the current position
	 * @return		A modified pixel
	 */
	Pixel operator+(const Pixel& other) const;

	/***
	 * Adds an offset encoded in the other pixel
	 *
	 * @param other	A pixel offset added to the current position
	 */
	void operator+=(const Pixel& other);

	/// Returns the current x value
	int x() const;

	/***
	 * Sets a new x value
	 *
	 * @param x		A new x value
	 */
	void setX(int x);

	/// Returns the current y value
	int y() const;

	/***
	 * Sets a new y value
	 *
	 * @param y 	A new y value
	 */
	void setY(int y);

private:

	/// x coordinate of the pixel
	int m_x;

	/// y coordinate of the pixel
	int m_y;
};


} /* namespace jumper */

#endif /* SRC_PIXEL_HPP_ */
