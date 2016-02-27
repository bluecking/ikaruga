//
// Created by Jochen Saalfeld on 27.02.16.
//

#ifndef SCROLLER_FONTRENDER_H
#define SCROLLER_FONTRENDER_H

#include "StaticRenderable.hpp"
#include <vector>

using std::string;
using std::vector;

namespace jumper {
    class FontRender : public StaticRenderable {
    public:
        FontRender(int tileHeight,
                   int tileWidth,
                   SDL_Renderer* renderer,
                   SDL_Texture* texture);
        vector<Vector2i> renderNumber(int number, int numberOffset);
        vector<Vector2i> renderString(string str, int minusculeOffset, int capitalOffset);
    private:
        int m_tileHeight;
        int m_tileWidth;

    };
}

#endif //SCROLLER_FONTRENDER_H
