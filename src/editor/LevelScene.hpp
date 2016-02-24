#ifndef LEVELSCENE_HPP
#define LEVELSCENE_HPP

#include<string>
#include"QGraphicsScene"
#include"QGraphicsView"
#include"QGraphicsItem"
#include<QTextStream>
#include<QFile>
#include"MainWindow.hpp"
#include"GraphicsTileItem.hpp"
#include"Settings.h"
#include<QGraphicsSceneMouseEvent>
#include<iostream>
#include "TextureScene.h"


class MainWindow;

class LevelScene : public QGraphicsScene
{
public:

    /// Loads des Level with the given filenale nad
    /// Stores a pointer to it's main window in a
    /// class valiable.
    LevelScene(QString filename, MainWindow* window);
	void setTileSettings(int index,int type, QRect rect);
	QPixmap** getPixmap();

protected:

    /// Is called whenever the mouse is pressend within
    /// the scene
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:

    GraphicsTileItem* textureItem;
    QRect m_rect;
    QPixmap** m_pixmap;   // A QPixmap to store the tile bitmap
	int** m_tiles;        // The 2D tile array
	int m_index=0;        // Tile id
	int m_type=0;         // texture type
	int m_tileWidth;      // Width of the tiles
	int m_tileHeight;     // Height of the tiles
	int m_tilesPerRow;    // Tiles per row in the tile bitmap
	int m_numRows;        // Number of rows in the tile bitmap
	int m_tileOffset;     // Offset between the tiles
	int m_levelWidth;     // Level width (in tiles)
	int m_levelHeight;    // Level height in tiles
	int m_keyR;           // Key color r component
	int m_keyG;           // Key color g component
	int m_keyB;           // Key color b component
	std::string m_texFileName; // File name of the tile bitmap
	std::string m_enemyFileName;
	std::string m_playerFileName;
	Settings m_setting;

	MainWindow* m_mainWindow; // Pointer to a main window
        
};

#endif
