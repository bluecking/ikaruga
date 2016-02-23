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

/**
 * @brief A camera object to scroll within a level
 */
class Camera
{
public:

	/**
	 * @brief Constructs a camera at (0, 0)
	 */
	Camera();

	/**
	 * @brief Constructs a camera with the given pixel offsets
	 */
	Camera(const Vector2f& pixel, int w, int h);

	/**
	 * @brief 	Moves the camera to the given position. Reference point is the
	 * 			middle of the represented frustrum
	 *
	 * @param position	The new camera position
	 */
	void move(const Vector2f& position);

	/// Returns the current x-position
	float x();

	/// Returns the current y-position
	float y();

	/// Returns the current position
	Vector2f& position();

	/// Destructor
	virtual ~Camera();

	/// Returns the camera width
	int w();

	/// Returns the camera height
	int h();

	friend class MainWindow;
private:

	/// Current camera position
	Vector2f	m_position;

	/// Field of view width
	int			m_width;

	/// Field of view height
	int			m_height;

};

} /* namespace jumper */

#endif /* CAMERA_HPP_ */
