/*
 * LevelScene.cpp
 *
 *  Created on: Jul 23, 2015
 *      Author: twiemann
 */

#include "LevelScene.hpp"
#include "TilesetScene.hpp"
#include "GraphicsTileItem.hpp"



LevelScene::LevelScene(QString filename, MainWindow* window)
	: m_mainWindow(window)
{
	string fn = filename.toStdString();

	int viewWidth = window->graphicsViewTiles->width();

	ifstream in(fn.c_str());

	if(in.good())
	{
		in >> m_texFileName;
		in >> m_tileWidth >> m_tileHeight >> m_tilesPerRow >> m_numRows
		   >> m_tileOffset >> m_keyR >> m_keyG >> m_keyB >> m_levelWidth >> m_levelHeight;
	}

	m_pixmap = new QPixmap(QString(m_texFileName.c_str()));
	if(m_pixmap == 0)
	{
		cout << "Error: Unable to load pixmap from file " << m_texFileName << endl;
	}

	window->spinBoxX->setValue(m_levelWidth);
	window->spinBoxY->setValue(m_levelHeight);

	m_tiles = new int*[m_levelHeight];
	for(int i = 0; i < m_levelHeight; i++)
	{
		m_tiles[i] = new int[m_levelWidth];
		for(int j = 0; j < m_levelWidth; j++)
		{
			m_tiles[i][j] = 0;
		}
	}


	for(int i = 0; i < m_levelHeight; i++)
	{
		for(int j = 0; j < m_levelWidth; j++)
		{
			in >> m_tiles[i][j];

			int tileIndex = m_tiles[i][j] -1;
			int row = tileIndex / m_tilesPerRow;
			int col = tileIndex % m_tilesPerRow;

			int x, y;
			x = col * m_tileWidth;
			if(col > 0)
			{
				x += col * m_tileOffset;
			}

			y = row * m_tileHeight;
			if(row > 0)
			{
				y += row * m_tileOffset;
			}

			QRect rect(x, y, m_tileWidth, m_tileHeight);

			GraphicsTileItem* item;
			if(tileIndex >= 0)
			{
				item = new GraphicsTileItem(m_pixmap, rect, tileIndex);
			}
			else
			{
				QColor color(m_keyR, m_keyG, m_keyB);
				item = new GraphicsTileItem(&color, m_tileWidth, m_tileHeight);
			}

			item->setPos(j * m_tileWidth, i * m_tileHeight);
			addItem(item);
		}
	}

}

void LevelScene::save(string filename)
{
	ofstream out(filename.c_str());
	out << m_texFileName << endl;
	out << m_tileWidth  << " " << m_tileHeight << " " << m_tilesPerRow << " " << m_numRows << " "
		<< m_tileOffset << " " << m_keyR       << " " << m_keyG        << " " << m_keyB  << " " << m_levelWidth << " " << m_levelHeight << endl;


	for(int i = 0; i < m_levelHeight; i++)
	{
		for(int j = 0; j < m_levelWidth; j++)
		{
			out << m_tiles[i][j] << " ";
		}
		cout << endl;
	}
}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsScene::mousePressEvent(event);
	QPointF p = event->scenePos();
	GraphicsTileItem* item = static_cast<GraphicsTileItem*>(itemAt(event->scenePos()));

	if(event->button() == Qt::LeftButton)
	{

		if(item)
		{
			TilesetScene* scene = static_cast<TilesetScene*>(m_mainWindow->graphicsViewTiles->scene());

			if(scene->m_selectedItem)
			{
				item->setIndex(scene->m_selectedItem->getIndex());

				int tileIndex = scene->m_selectedItem->getIndex() -1;
				int row = tileIndex / m_tilesPerRow;
				int col = tileIndex % m_tilesPerRow;

				int x, y;
				x = col * m_tileWidth;
				if(col > 0)
				{
					x += col * m_tileOffset;
				}

				y = row * m_tileHeight;
				if(row > 0)
				{
					y += row * m_tileOffset;
				}

				QRect rect(x, y, m_tileWidth, m_tileHeight);

				QPixmap pm = m_pixmap->copy(rect);
				item->setPixmap(pm);
			}
			else
			{
				item->setIndex(0);

				QPixmap pm(m_tileWidth, m_tileHeight);
				pm.fill(QColor(m_keyR, m_keyG, m_keyB));
				item->setPixmap(pm);
			}

			// Update tile array
			int i = p.y() / m_tileHeight;
			int j = p.x() / m_tileWidth;

			//cout << i << " " << j << endl;

			if(scene->m_selectedItem)
			{
				m_tiles[i][j] = scene->m_selectedItem->getIndex();
			}
			else
			{
				m_tiles[i][j] = 0;
			}

		}
	}
	else
	{
		if(item->getIndex() > 0)
		{
			TilesetScene* scene = static_cast<TilesetScene*>(m_mainWindow->graphicsViewTiles->scene());
			if(item && scene)
			{
				scene->m_selectedItem = item;
			}
		}
	}
}


LevelScene::~LevelScene()
{
	// TODO Auto-generated destructor stub
}

