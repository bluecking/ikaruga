/*
 * LevelScene.h
 *
 *  Created on: Jul 23, 2015
 *      Author: twiemann
 */

#ifndef SRC_EDITOR_WIDGETS_LEVELSCENE_HPP_
#define SRC_EDITOR_WIDGETS_LEVELSCENE_HPP_

#include <iostream>
#include <fstream>
using namespace std;

#include <QtGui>

#include "EditorMainWindow.hpp"

class LevelScene : public QGraphicsScene
{
public:
	LevelScene(QString filename, MainWindow* window);
	virtual ~LevelScene();

	void save(string filename);

protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
	int** m_tiles;

	QPixmap* m_pixmap;
	int m_tileWidth;
	int m_tileHeight;
	int m_tilesPerRow;
	int m_numRows;
	int m_tileOffset;
	int m_levelWidth;
	int m_levelHeight;
	int m_keyR;
	int m_keyG;
	int m_keyB;
	string m_texFileName;

	MainWindow* m_mainWindow;
};

#endif /* SRC_EDITOR_WIDGETS_LEVELSCENE_HPP_ */
