/*
 * QGraphicsTileItem.cpp
 *
 *  Created on: Jul 23, 2015
 *      Author: twiemann
 */

#include <QGraphicsColorizeEffect>

#include "GraphicsTileItem.hpp"
#include "TilesetScene.hpp"

#include <iostream>
using namespace std;

GraphicsTileItem::GraphicsTileItem(QPixmap* tileset, const QRect& rect, int index)
	: m_index(index)
{
	// Get correspondig sub-pixmap
	QPixmap pm = tileset->copy(rect);
	setPixmap(pm);

}

GraphicsTileItem::GraphicsTileItem(QColor* color, int w, int h)
	: m_index(-1)
{
	QPixmap pm(w, h);
	pm.fill(*color);
	setPixmap(pm);
}

void GraphicsTileItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{

}

GraphicsTileItem::~GraphicsTileItem()
{
	// TODO Auto-generated destructor stub
}

