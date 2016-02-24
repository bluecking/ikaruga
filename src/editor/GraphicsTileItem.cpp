#include"GraphicsTileItem.hpp"
#include<iostream>


/// Constructor. Creates a sub-pixmap from tileset at position rect
    /// and stores the given index
GraphicsTileItem::GraphicsTileItem(QPixmap** tileset, const QRect& rect, int index, int type):QGraphicsPixmapItem()
{
    this->setPixmap(tileset[type]->copy(rect));
    m_index=index;
}

GraphicsTileItem::GraphicsTileItem(QPixmap* tileset, const QRect& rect, int index):QGraphicsPixmapItem()
{
    this->setPixmap(tileset->copy(rect));
    m_index=index;
}
    
    /// Constructor. Creartes an item with given color, width w and height h.
GraphicsTileItem::GraphicsTileItem(QColor* color, int w, int h):QGraphicsPixmapItem()
{

}
	    
    /// Is called when the mouse is pressed on the item
void GraphicsTileItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	std::cout<<"Doubleclicked: ";
	std::cout<<m_index<<std::endl;
}
