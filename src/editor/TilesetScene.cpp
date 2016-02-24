/*
 * TilesetScene.cpp
 *
 *  Created on: Jul 23, 2015
 *      Author: twiemann
 */

#include "TilesetScene.hpp"
#include "GraphicsTileItem.hpp"

#include <iostream>
#include <fstream>
using std::string;
using std::ifstream;
using std::cout;
using std::endl;


TilesetScene::TilesetScene(QString& filename, MainWindow* window)
	: m_selectedItem(0)
{
	string fn = filename.toStdString();
	string texFileName;

	int tileWidth;
	int tileHeight;
	int tilesPerRow;
	int numRows;
	int tileOffset;
	unsigned char keyR;
	unsigned char keyG;
	unsigned char keyB;

	int viewWidth = window->graphicsViewTiles->width();



	ifstream in(fn.c_str());

	if(in.good())
	{
		in >> texFileName;
		in >> tileWidth >> tileHeight >> tilesPerRow >> numRows
		   >> tileOffset >> keyR >> keyG >> keyB;
	}

	QPixmap* pixmap = new QPixmap(QString(texFileName.c_str()));
	if(pixmap == 0)
	{
		cout << "Error: Unable to load pixmap from file " << texFileName << endl;
	}

	cout << pixmap->width() << " " << pixmap->height() <<endl;

	int viewTilesPerRow = viewWidth / tileWidth - 1;

	int c = 0;
	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j < tilesPerRow; j++)
		{
			int x = j * tileWidth;
			int y = i * tileHeight;

			if(j > 0)
			{
				x += j * tileOffset;
			}

			if(i > 0)
			{
				y += i * tileOffset;
			}

			QRect rect(x, y, tileWidth, tileHeight);

			GraphicsTileItem* item = new GraphicsTileItem(pixmap, rect, c + 1);

			// Compute Screen position
			y = c / viewTilesPerRow;
			x = c % viewTilesPerRow;

			item->setPos(x * tileWidth,y * tileHeight);

			cout << x * tileWidth << " " << y * tileHeight << endl;

			addItem(item);

			c++;
		}
	}

	in.close();
}

void TilesetScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsScene::mousePressEvent(event);
	QPointF p = event->scenePos();
	GraphicsTileItem* item = static_cast<GraphicsTileItem*>(itemAt(event->scenePos()));

	if(item)
	{
		m_selectedItem = item;
		cout << item->getIndex() << endl;
	}
}

TilesetScene::~TilesetScene()
{
	// TODO Auto-generated destructor stub
}

