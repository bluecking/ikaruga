/*
 * TilesetScene.hpp
 *
 *  Created on: Jul 23, 2015
 *      Author: twiemann
 */

#ifndef SRC_EDITOR_WIDGETS_TILESETSCENE_HPP_
#define SRC_EDITOR_WIDGETS_TILESETSCENE_HPP_

#include <QGraphicsScene>

#include "GraphicsTileItem.hpp"
#include "../app/EditorMainWindow.hpp"

class TilesetScene : public QGraphicsScene
{
public:
	GraphicsTileItem* m_selectedItem;

	TilesetScene(QString& filename, MainWindow* window);
	virtual ~TilesetScene();

protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

#endif /* SRC_EDITOR_WIDGETS_TILESETSCENE_HPP_ */
