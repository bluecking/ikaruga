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
        m_rectSource.w = tileWidth;
        m_rectSource.h = tileHeight;
        m_rectTarget.w = tileWidth;
        m_rectTarget.h = tileHeight;
        m_stringPropertiesSet = false;
        m_tablePropertiesSet = false;
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
        m_tablePropertiesSet = true;
        m_tableProperties.positionX = properties.positionX;
        m_tableProperties.positionY = properties.positionY;
        m_tableProperties.width = properties.width;
        m_tableProperties.height = properties.height;
    }

    void RenderTable::render()
    {
        if (!m_stringPropertiesSet || !m_tablePropertiesSet)
        { throw std::domain_error("You have to use setStringProperties and setTableProperties first."); }

        for(int i = 0; i < m_content.size(); i++) //loop rows
        {
            for(int j = 0; j < m_content[i].size(); j++) //loop columns
            {
                m_textLine = renderString(m_content[i][j], m_minusculeOffset, m_capitalOffset, m_numberOffset);
                for (int k = 0; k < m_textLine.size(); k++) //print column content
                {
                    m_rectSource.x = m_textLine[k].x();
                    m_rectSource.y = m_textLine[k].y();

                    m_rectTarget.x = m_tableProperties.positionX + k * m_tileWidth;
                    m_rectTarget.y = m_tableProperties.positionY + i * m_tileHeight;
                    //std::cout << "recS_Px" << m_rectSource.x << "recS_Py" << m_rectSource.y << "recS_w" << m_rectSource.w << "recS_h" << m_rectSource.h << std::endl;
                    //std::cout << "recT_Px" << m_rectTarget.x << "recT_Py" << m_rectTarget.y << "recT_w" << m_rectTarget.w << "recT_h" << m_rectTarget.h << std::endl << std::endl;
                    SDL_RenderCopy(m_renderer, m_texture, &m_rectSource, &m_rectTarget);
                }
            }
        }
    }
} //end of namespace jumper
