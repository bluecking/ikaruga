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
	void setSize(int value);
	void setBot(QString botName);
	void setPower(QString powerName);
	void setNull();
	void setId(int id);
	void setLevelName(QString levelName);

	QString toQString(std::string string);

	QPixmap* getPixmap();

protected:

    /// Is called whenever the mouse is pressend within
    /// the scene
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:

    QRect m_rect;
    QPixmap* m_pixmap;   // A QPixmap to store the tile bitmap
	QString	m_fileName;
	QString m_path;
	XML* m_xml;
	QString m_xmlFileName;
	QString m_levelName;
	QString m_imgTexture; // File name of the tile bitmap
	QString m_imgBackground;
	QString m_imgStatusbar;
	QString m_imgPlayer;
	QString m_xmlLevelName;
	Settings m_setting;
	std::string m_soundfile;
	std::string m_botType;
	std::string m_color;
	std::vector<XML::LevelBot> m_levelBots;
	std::vector<XML::LevelItem> m_levelItems;
	std::vector<XML::Bot> m_bots;
	std::vector<XML::Item> m_items;
	std::vector<XML::Weapon> m_weapons;
	XML::LevelItem m_levelItem;
	XML::Item m_item;
	XML::Bot m_bot;
	XML::Weapon m_weapon;
	XML::LevelBot m_levelbot;
	XML::Background m_background;
	XML::Statusbar m_statusbar;
	XML::Player m_player;
	std::vector<int>* m_tiles;        // The 2D tile array
	int m_typeItem;
	int m_typeBot;
	int m_typeTexture;
	int m_scrollSpeed;
	int m_index=0;        // Tile id
	int m_type=0;         // texture type
	int m_tileWidth;      // Width of the tiles
	int m_tileHeight;     // Height of the tiles
	int m_tilesPerRow;    // Tiles per row in the tile bitmap
	int m_numRows;        // Number of rows in the tile bitmap
	int m_tileOffset;     // Offset between the tiles
	int m_levelWidth;     // Level width (in tiles)
	int m_levelHeight;    // Level height in tiles
	int m_levelId;




	MainWindow* m_mainWindow; // Pointer to a main window
        
};

#endif
