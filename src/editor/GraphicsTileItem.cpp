#include"GraphicsTileItem.hpp"


/// Constructor. Creates a sub-pixmap from tileset at position rect
    /// and stores the given index
GraphicsTileItem::GraphicsTileItem(QPixmap** tileset, const QRect& rect, int index, int type):QGraphicsPixmapItem()
{
    mainWindow=true;
    m_type=type;
    m_pixmap=tileset;
    this->setPixmap(m_pixmap[type]->copy(rect));
    m_index=index;
}

GraphicsTileItem::GraphicsTileItem(QPixmap* tileset, const QRect& rect, int index, int type):QGraphicsPixmapItem()
{
    mainWindow=false;
    m_type=type;
    m_rect=rect;
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
    m_type=tileset_id;
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
	    
    /// Is called when the mouse is pressed on the item
void GraphicsTileItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	std::cout<<"Doubleclicked: ";
    //Player* x=new Player();
    //ItemSettingsGui* gui=new ItemSettingsGui(x);
    //gui->show();
	std::cout<<m_index<<std::endl;
}
