/*
 * QGraphicsTileItem.h
 *
 *  Created on: Jul 23, 2015
 *      Author: twiemann
 */

#ifndef SRC_EDITOR_WIDGETS_GRAPHICSTILEITEM_HPP_
#define SRC_EDITOR_WIDGETS_GRAPHICSTILEITEM_HPP_

#include <QtGui>

class GraphicsTileItem : public QGraphicsPixmapItem
{
public:
	GraphicsTileItem(QPixmap* tileset, const QRect& rect, int index);
	GraphicsTileItem(QColor* color, int w, int h);
	virtual ~GraphicsTileItem();
	int getIndex() const { return m_index;}
	void setIndex(int i) {m_index = i;}

protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
	int m_index;
};

#endif /* SRC_EDITOR_WIDGETS_GRAPHICSTILEITEM_HPP_ */
