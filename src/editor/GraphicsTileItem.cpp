#include"GraphicsTileItem.hpp"



GraphicsTileItem::GraphicsTileItem(QPixmap* tileset, const QRect& rect, int index, int type):QGraphicsPixmapItem()
{
    this->setPixmap(tileset->copy(rect));
    m_pixmap=tileset;
    m_type=type;
    m_rect=rect;
    m_index=index;
}


void GraphicsTileItem::changeItem(QPixmap* map,QRect& rect,int type)
{
    this->setPixmap(map->copy(rect));
    m_type=type;
}

void GraphicsTileItem::changeItem(QPixmap* map,QRect& rect,int type,int index)
{
    this->setPixmap(map->copy(rect));
    m_type=type;
    m_index=index;

}

int GraphicsTileItem::getType()
{
    return m_type;
}


QRect GraphicsTileItem::getRect()
{
    return m_rect;
}

