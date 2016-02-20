/*
 * Path.hpp
 *
 *  Created on: Jan 8, 2016
 *      Author: twiemann
 */

#ifndef SRC_PATH_HPP_
#define SRC_PATH_HPP_

#include "StaticRenderable.hpp"

#include <list>
using std::list;

namespace jumper
{

/*
 *
 */
class Path: public StaticRenderable
{
public:
	Path(SDL_Renderer* renderer, std::list<Vector2f> path);
	virtual void render();
	virtual ~Path();
private:
	std::list<Vector2f> m_path;
};

} /* namespace jumper */

#endif /* SRC_PATH_HPP_ */
