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
#include<QGraphicsSceneMouseEvent>
#include<iostream>
#include "TextureScene.hpp"
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
	void setBackgroundSize(int levelWidth);
	void setItem(QGraphicsSceneMouseEvent *event);
	QString toQString(std::string string);
	QPixmap* getPixmap();

protected:

    /// Is called whenever the mouse is pressend within
    /// the scene
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

private:
	void setSceneRect();

    QRect m_rect;									// last copied rect
    QPixmap* m_pixmap;   							// A QPixmap to store the tile bitmap
	QString m_path;									// path to levels directory
	XML* m_xml;										// xml object for XML library
	QString m_levelName;							// name of .lvl file
	QString m_imgTexture; 							// path of the tile texture
	QString m_imgBackground;						// path of the background texture
	QString m_imgExplosion;                         // path of the explosion texture
	QString m_imgStatusbar;							// path of the statusbar texture
	QString m_imgPlayer;							// path of the player texture
	QString m_xmlLevelName;							// name of the level
	std::string m_soundfile;						// path of the background soundfile
	std::string m_color;							// color to render bots
	std::vector<XML::LevelBot> m_levelBots;			// bots for the xml file
	std::vector<XML::LevelItem> m_levelItems;		// items for the xml file
	std::vector<XML::Bot> m_bots;					// properties of bots
	std::vector<XML::Item> m_items;					// properties of items
	std::vector<XML::Weapon> m_weapons;				// properties of weapons
	XML::Item m_item;								// item to set in the mainView
	XML::Bot m_bot;									// bot to set in the mainView
	XML::Weapon m_weapon;							// weapons to set in the xml file
	XML::Background m_background;					// background properties for xml file
	XML::Statusbar m_statusbar;						// statusbar properties for the xml file
	XML::Player m_player;							// player properties for the xml file
    std::vector<int>* m_tiles;        				// The 2D tile array
    QGraphicsItemGroup* m_backgroundGroupe;         // background layer
    int m_typeBackground;							// int for background type
	int m_typeItem;									// int for item type
	int m_typeBot;									// int for bot type
	int m_typeTexture;								// int for texture type
	int m_scrollSpeed;                              // background scrollspeed
	int m_index;                                    // Tile id
	int m_type;                                     // texture type
	int m_tileWidth;                                // Width of the tiles
	int m_tileHeight;                               // Height of the tiles
	int m_tilesPerRow;                              // Tiles per row in the tile bitmap
	int m_numRows;                                  // Number of rows in the tile bitmap
	int m_tileOffset;                               // Offset between the tiles
	int m_levelWidth;                               // Level width in tiles
	int m_levelHeight;                              // Level height in tiles
	int m_levelId;                                  // Level id
	int m_backgroundHeight;							// background tile height
	int m_backgroundWidth;							// backgoround tile Width
	int m_lastX;
	int m_lastY;





	MainWindow* m_mainWindow; // Pointer to a main window
        
};

#endif
