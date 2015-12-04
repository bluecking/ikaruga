/*
 * Camera.hpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Vector.hpp"
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
	Camera(const Vector2i& pixel);

	/***
	 * Moves the camera according to the given offset
	 * @param offset	A pixel offset for camera movement
	 */
	void move(const Vector2i& offset);

	/// Returns the current x-position
	int x();

	/// Returns the current y-position
	int y();

	/// Returns the current position
	Vector2i& position();

	/// Destructor
	virtual ~Camera();

private:

	/// Current camera position
	Vector2i	m_position;

};

} /* namespace jumper */

#endif /* CAMERA_HPP_ */
