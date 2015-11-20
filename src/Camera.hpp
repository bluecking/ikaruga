/*
 * Camera.hpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Pixel.hpp"

namespace jumper
{

/***
 * A camera object to scroll within a level
 */
class Camera
{
public:

	/***
	 * Constructs a camera at (0, 0)
	 */
	Camera();

	/***
	 * Constructs a camera with the given pixel offsets
	 */
	Camera(const Pixel& pixel);

	/***
	 * Moves the camera according to the given offset
	 * @param offset	A pixel offset for camera movement
	 */
	void move(const Pixel& offset);

	/// Returns the current x-position
	int x();

	/// Returns the current y-position
	int y();

	/// Returns the current position
	Pixel position() const;

	/// Destructor
	virtual ~Camera();

private:

	/// Current camera position
	Pixel	m_position;

};

} /* namespace jumper */

#endif /* CAMERA_HPP_ */
