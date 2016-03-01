#include"GraphicsTileItem.hpp"


/// Constructor. Creates a sub-pixmap from tileset at position rect
    /// and stores the given index

GraphicsTileItem::GraphicsTileItem(QPixmap* tileset, const QRect& rect, int index, int type):QGraphicsPixmapItem()
{
    mainWindow=false;
    m_pixmap=tileset;
    m_type=type;
    m_rect=rect;
    m_index=index;
    this->setPixmap(tileset->copy(rect));
}
    
    /// Constructor. Creartes an item with given color, width w and height h.
GraphicsTileItem::GraphicsTileItem(QColor* color, int w, int h):QGraphicsPixmapItem()
{

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

bool GraphicsTileItem::getWindowType()
{
    return mainWindow== true;
}

QRect GraphicsTileItem::getRect()
{
    return m_rect;
}
	    


GraphicsTileItem::~GraphicsTileItem()
{
}
