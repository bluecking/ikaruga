//
// Created by johann on 23.02.16.
//

#ifndef LEVELVIEW_TEXTURESCENE_H
#define LEVELVIEW_TEXTURESCENE_H

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
#include"Settings.h"

class MainWindow;

class TextureScene : public QGraphicsScene
{
public:
    /// Loads des Level with the given filenale nad
    /// Stores a pointer to it's main window in a
    /// class valiable.
    TextureScene(Settings setting, QGraphicsView* View, MainWindow* window);
    TextureScene(){};

    QGraphicsScene* getScene();

protected:
    /// Is called whenever the mouse is pressend within
    /// the scene
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
private:
    int** m_tiles;        // The 2D tile array
    QPixmap* m_pixmap;    // A QPixmap to store the tile bitmap
    int m_tileWidth;      // Width of the tiles
    int m_tileHeight;     // Height of the tiles
    int m_tilesPerRow;    // Tiles per row in the tile bitmap
    int m_numRows;        // Number of rows in the tile bitmap
    int m_textureHeight;     // Level width (in tiles)
    int m_textureWidth;    // Level height in tiles
    int m_keyR;           // Key color r component
    int m_keyG;           // Key color g component
    int m_keyB;           // Key color b component
    std::string m_texFileName; // File name of the tile bitmap
    MainWindow* m_mainWindow; // Pointer to a main window

};

#endif //LEVELVIEW_TEXTURESCENE_H
