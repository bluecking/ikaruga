#ifndef GRAPHICS_TILE_ITEM_HPP
#define GRAPHICS_TILE_ITEM_HPP
#include "QGraphicsPixmapItem"
#include<iostream>
//#include "itemsettingsgui.h"

class GraphicsTileItem : public QGraphicsPixmapItem
{
  
public:
  
    /// Constructor. Creates a sub-pixmap from tileset at position rect
    /// and stores the given index

	GraphicsTileItem(QPixmap* tileset, const QRect& rect, int index, int type);
    
    /// Constructor. Creartes an item with given color, width w and height h.
	GraphicsTileItem(QColor* color, int w, int h);
    
    /// Destructor.
  virtual ~GraphicsTileItem();

    /// Returns the tile index of the item
    int getIndex() const { return m_index;}
	void changeItem(QPixmap* map,QRect& rect,int type);
	void changeItem(QPixmap* map,QRect& rect,int type,int index);
	bool getWindowType();
	QRect getRect();
	int getType();

    /// Sets the tile index of the item
    void setIndex(int i) {m_index = i;}


private:
    
    /// The tile index
	int m_index;
	int m_type;
	QPixmap* m_pixmap;
	bool mainWindow=false;
	QRect m_rect;
};

#endif
