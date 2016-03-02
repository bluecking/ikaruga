/**
* @file RenderTable.c
* @brief $BRIEF_DESCRIPTION
*
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
* @author Timo Osterkamp (tosterkamp@uni-osnabrueck.de)
* @date 02 Mrz 2016
*/
#include "RenderTable.hpp"

namespace jumper
{
    RenderTable::RenderTable(SDL_Renderer* renderer, SDL_Texture* textureint, int tileHeight, int tileWidth) :
    FontRender(tileHeight, tileWidth, renderer, textureint)
    {
        m_renderer = renderer;
        m_texture = textureint;
        m_tileHeight = tileHeight;
        m_tileWidth = tileWidth;
    }

    void RenderTable::setStringProperties(int minusculeOffset, int capitalOffset,
                                          int numberOffset, std::vector<std::vector<std::string>> content)
    {
        m_stringPropertiesSet = true;
        m_minusculeOffset = minusculeOffset;
        m_capitalOffset = capitalOffset;
        m_numberOffset = numberOffset;
        m_content = content;
    }

    void RenderTable::setTableProperties(RenderTable::tableProperties properties)
    {
        m_tableProperties.positionX = properties.positionX;
        m_tableProperties.positionY = properties.positionY;
        m_tableProperties.width = properties.width;
        m_tableProperties.height = properties.height;
    }

    void RenderTable::render()
    {
        if (!m_stringPropertiesSet)
        { throw std::domain_error("You have to use setStringProperties first."); }

        m_rectSource.w = m_tileWidth;
        m_rectSource.h = m_tileHeight;
        m_rectTarget.w = m_tileWidth;
        m_rectTarget.h = m_tileHeight;

        m_textLine = renderString(m_content[0][0], m_minusculeOffset, m_capitalOffset, m_numberOffset);
       for (int j = 0; j < m_textLine.size(); j++)
        {
            m_rectSource.x = m_textLine[j].x();
            m_rectSource.y = m_textLine[j].y();

            m_rectTarget.x = m_tableProperties.positionX + j * m_tileWidth;
            m_rectTarget.y = m_tableProperties.positionY;
            //std::cout << "recS_Px" << m_rectSource.x << "recS_Py" << m_rectSource.y << "recS_w" << m_rectSource.w << "recS_h" << m_rectSource.h << std::endl;
            //std::cout << "recT_Px" << m_rectTarget.x << "recT_Py" << m_rectTarget.y << "recT_w" << m_rectTarget.w << "recT_h" << m_rectTarget.h << std::endl << std::endl;
            SDL_RenderCopy(m_renderer, m_texture, &m_rectSource, &m_rectTarget);
        }
    }
} //end of namespace jumper
