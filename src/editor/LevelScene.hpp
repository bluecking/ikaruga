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
#include"../xml/XML.hpp"


class MainWindow;

class LevelScene : public QGraphicsScene
{
public:

    /// Loads des Level with the given filenale nad
    /// Stores a pointer to it's main window in a
    /// class valiable.
    LevelScene(QString filename, MainWindow* window);
	void setTileSettings(int index,int type, QRect rect);
	void saveLevel(QString fileName);
	void saveXml(QString fileName);
	void loadXml(QString fileName);
	void loadLevel(QString fileName);
	QString toQString(std::string string);

	QPixmap** getPixmap();

protected:

    /// Is called whenever the mouse is pressend within
    /// the scene
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:

    GraphicsTileItem* textureItem;
    QRect m_rect;
    QPixmap** m_pixmap;   // A QPixmap to store the tile bitmap
	QString	m_fileName;
	QString m_path;
	XML* m_xml;
	XML::Player m_player;
	QString m_xmlFileName;
	QString m_levelId;
	QString m_levelName;
	QString m_texFileName; // File name of the tile bitmap
	QString m_enemyFileName;
	QString m_playerFileName;
	Settings m_setting;
	std::vector<XML::LevelBot> m_bots;

	/**=m_xml->getLevelBot();
	=m_xml->getLevelBots();
	=m_xml->getBot();
	=m_xml->getItem();
	=m_xml->getItems();
	=m_xml->getLevelItem();
	=m_xml->getWeapon();
	=m_xml->getWeapons();
	=m_xml->getBackground();
	=m_xml->getBots();
	=m_xml->getLevelItems();
	=m_xml->getLevelname();
	=m_xml->getPlayer();*/

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



	MainWindow* m_mainWindow; // Pointer to a main window
        
};

#endif
