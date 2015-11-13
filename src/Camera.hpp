/*
 * Camera.hpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

namespace jumper
{

/***
 * A camera object to scroll within a level
 */
class Camera
{
public:

	/***
	 * Constructs a camera with the given pixel offsets
	 */
	Camera(int x = 0, int y = 0);

	/***
	 * Moves the camera by the given amount of pixels in x-direction. Positive
	 * values indicate movement to the right, negative values
	 * move the camera to the left
	 */
	void moveX(int pixels);

	/***
	 * Moves the camera by the given amount of pixels in y-direction. Positive
	 * values indicate downward movement, negative value indicate upward movement
	 */
	void moveY(int pixels);

	/// Returns the current x-position
	int x();

	/// Returns the current y-position
	int y();

	/// Destructor
	virtual ~Camera();

private:

	/// X-Position of the camera
	int m_x;

	/// Y-Position of the camera
	int m_y;
};

} /* namespace jumper */

#endif /* CAMERA_HPP_ */
