/**
* @file RenderTable.h
* @brief $BRIEF_DESCRIPTION
*
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
* @author Timo Osterkamp (tosterkamp@uni-osnabrueck.de)
* @date 02 Mrz 2016
*/
#include "FontRender.hpp"

#ifndef SCROLLER_RENDERTABLE_HPP
#define SCROLLER_RENDERTABLE_HPP

namespace jumper
{
    class RenderTable : public FontRender
    {
    public:
        struct tableProperties {
            int positionX;
            int positionY;
            int width;
            int height;
        };

        RenderTable(SDL_Renderer *renderer, SDL_Texture * defaultTtexture, int tileHeight, int tileWidth);

        void setStringProperties(int minusculeOffset, int capitalOffset, int numberOffset, std::vector<std::vector<std::string>> content);

        void setTableProperties(tableProperties properties);

    private:
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
        int m_tileHeight;
        int m_tileWidth;
        int m_minusculeOffset;
        int m_capitalOffset;
        int m_numberOffset;
        tableProperties m_tableProperties;
        std::vector<std::vector<std::string>> m_content;
        vector<Vector2i> m_textLine;
        SDL_Rect m_rectSource;
        SDL_Rect m_rectTarget;
        bool m_stringPropertiesSet;
        bool m_tablePropertiesSet;
    public:
        virtual void render();
    };
} //end of namespace jumper
#endif //SCROLLER_RENDERTABLE_HPP
