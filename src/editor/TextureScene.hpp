#ifndef LEVELVIEW_TEXTURESCENE_HPP
#define LEVELVIEW_TEXTURESCENE_HPP

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
#include"LevelScene.hpp"

class MainWindow;
class LevelScene;

class TextureScene : public QGraphicsScene
{
public:
    /// Loads des Level with the given filenale nad
    /// Stores a pointer to it's main window in a
    /// class valiable.
    TextureScene(QGraphicsView* View,LevelScene* level, MainWindow* window);
    TextureScene(){};

    QGraphicsScene* getScene();

protected:

    /// Is called whenever the mouse is pressend within
    /// the scene
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:

    LevelScene* m_levelScene;
    int m_tileWidth;      // Width of the tiles
    int m_tileHeight;     // Height of the tiles
    int m_tilesPerRow;    // Tiles per row in the tile bitmap
    int m_numRows;        // Number of rows in the tile bitmap
    int m_textureHeight;  // Level width (in tiles)
    int m_textureWidth;    // Level height in tiles
    int m_type=0;

};

#endif //LEVELVIEW_TEXTURESCENE_HPP
