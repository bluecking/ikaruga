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

    /// Returns the tile index of the item
    int getIndex() const { return m_index;}

	void changeItem(QPixmap* map,QRect& rect,int type);

	void changeItem(QPixmap* map,QRect& rect,int type,int index);

	QRect getRect();

	int getType();

	/// Sets the tile index of the item
    void setIndex(int i) {m_index = i;}

	/// Destructor.
	virtual ~GraphicsTileItem(){};

private:
    

	int m_index;					//tile index
	int m_type;                     //type of Texture
	QPixmap* m_pixmap;              //Texture to copy from
	QRect m_rect;
};

#endif
