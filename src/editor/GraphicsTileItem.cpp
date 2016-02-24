#include"GraphicsTileItem.hpp"
#include<iostream>


/// Constructor. Creates a sub-pixmap from tileset at position rect
    /// and stores the given index
GraphicsTileItem::GraphicsTileItem(QPixmap** tileset, const QRect& rect, int index, int type):QGraphicsPixmapItem()
{
    mainWindow=true;
    m_pixmap=tileset;
    m_rect=rect;
    this->setPixmap(m_pixmap[type]->copy(rect));
    m_index=index;
}

GraphicsTileItem::GraphicsTileItem(QPixmap* tileset, const QRect& rect, int index, int type):QGraphicsPixmapItem()
{
    m_type=type;
    this->setPixmap(tileset->copy(rect));
    m_index=index;
}
    
    /// Constructor. Creartes an item with given color, width w and height h.
GraphicsTileItem::GraphicsTileItem(QColor* color, int w, int h):QGraphicsPixmapItem()
{

}

void GraphicsTileItem::changeItem(int tileset_id,QRect& rect,int index)
{
    this->setPixmap(m_pixmap[tileset_id]->copy(rect));
    m_index=index;
}

int GraphicsTileItem::getType()
{
    return m_type;
}

bool GraphicsTileItem::getWindowType()
{
    return mainWindow;
}

QRect GraphicsTileItem::getRect()
{
    return m_rect;
}
	    
    /// Is called when the mouse is pressed on the item
void GraphicsTileItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	std::cout<<"Doubleclicked: ";
	std::cout<<m_index<<std::endl;
}
