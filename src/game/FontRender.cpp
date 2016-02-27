//
// Created by Jochen Saalfeld on 27.02.16.
//

#include "FontRender.hpp"
#include <list>

using std::string;
using std::vector;

namespace jumper{
    FontRender::FontRender(int tileHeight,
                           int tileWidth,
                           SDL_Renderer* renderer,
                           SDL_Texture* texture ):StaticRenderable(renderer, texture)
    {
        m_tileHeight = tileHeight;
        m_tileWidth = tileWidth;
    }
    vector<Vector2i> FontRender::renderNumber(int number, int numberOffset)
    {
        vector<Vector2i> retVal;
        std::list<int> digits;

        if (0 == number) {
            digits.push_back(0);
        }
        else {
            while (number != 0) {
                int last = number % 10;
                digits.push_front(last);
                number = (number - last) / 10;
            }
        }

        for (std::list<int>::iterator it = digits.begin(); it != digits.end(); it++) {
            int num = *it;
            Vector2i source;
            source.setX(num * m_tileWidth);
            source.setY(numberOffset);
            retVal.push_back(source);
        }
        return retVal;
    }
    vector<Vector2i> FontRender::renderString(string str, int minusculeOffset, int capitalOffset)
    {
        vector<Vector2i> retVal;
        return retVal;
    }
}