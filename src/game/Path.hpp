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

namespace jumper {

    /**
     *@brief A class representing a path of 2D points
     */
    class Path : public StaticRenderable {
    public:

        /**
         * @brief Creates a path object for the given SDL_Renderer from
         * 		  the given set of 2D points
         *
         * @param renderer		A valid SDL_Renderer struct
         * @param path			A list of 2D points
         */
        Path(SDL_Renderer *renderer, std::list<Vector2f> path);

        /// Renders the path
        virtual void render();

        /// Destructor
        virtual ~Path();

    private:
        std::list<Vector2f> m_path;
    };

} /* namespace jumper */

#endif /* SRC_PATH_HPP_ */
