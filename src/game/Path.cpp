/*
 * Path.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: twiemann
 */

#include "Path.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace jumper {

    Path::Path(SDL_Renderer *renderer, std::list<Vector2f> path)
            : StaticRenderable(renderer), m_path(path) {

    }

    void Path::render() {
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 0);
        bool first = true;
        Vector2f prev;
        for (const Vector2f v : m_path) {
            if (first == false) {
                int sx = prev.x() - m_camera.x();;
                int sy = prev.y() - m_camera.y();
                int ex = v.x() - m_camera.x();;
                int ey = v.y() - m_camera.y();

                SDL_RenderDrawLine(m_renderer, sx, sy, ex, ey);
            }
            else {
                first = false;
            }
            prev = v;
        }
    }

    Path::~Path() {
        // TODO Auto-generated destructor stub
    }

} /* namespace jumper */
