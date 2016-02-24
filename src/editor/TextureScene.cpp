//
// Created by johann on 23.02.16.
//
#include "TextureScene.h"

TextureScene::TextureScene(Settings setting,QGraphicsView* View,LevelScene* level, MainWindow* window) : QGraphicsScene(window) {

    ///Set tilesettings
    if (View->objectName().toStdString() == "EnemieView")
    {
        m_tilesPerRow = 2;
        m_numRows = 10;
        m_tileWidth = 40;
        m_tileHeight = 40;
        m_type=1;
    }
    else if(View->objectName().toStdString() == "TextureView")
    {
        m_tilesPerRow = 10;
        m_numRows = 4;
        m_tileWidth = 40;
        m_tileHeight = 40;
        m_type=0;
    }
    else if(View->objectName().toStdString() == "PlayerView")
    {
        m_tilesPerRow = 2;
        m_numRows = 1;
        m_tileWidth = 40;
        m_tileHeight = 80;
        m_type=2;
    }

    m_levelScene=level;
    int count = 1;
    int max = m_tilesPerRow * m_numRows;
    m_textureWidth = (int) (View->geometry().width() / m_tileWidth);
    m_textureHeight = (int) ((max) / m_textureWidth + ((View->geometry().width() % m_tileWidth) > 0 ? 0 : 1));


    for(int i = 0; i < m_textureHeight; i++)
    {
        for(int j = 0; j < m_textureWidth; j++)
        {
            ///puts tile_id in m_tiles
            int tile_id= count-1;

            ///creates Qrect if m_tiles >=0
            if(tile_id>=0)
            {
                QRect rect((m_tileWidth)*(tile_id%m_tilesPerRow),(m_tileHeight)*((int)(tile_id/m_tilesPerRow)),m_tileWidth,m_tileHeight);

                ///creates new GraphicsTileItem
                GraphicsTileItem *item = new GraphicsTileItem(m_levelScene->getPixmap()[m_type],rect,tile_id,m_type);

                ///sets Position of the rect and adds it to the scene
                item->setPos(m_tileWidth*j,m_tileHeight*i);
                this->addItem(item);
            }
            count++;
        }
    }
}

QGraphicsScene* TextureScene::getScene()
{
    return this;
}


void TextureScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    ///Calculates Clickposition and the containing Items
    int x = event->scenePos().x()/m_tileWidth;
    int y = event->scenePos().y()/m_tileHeight;
    QList<QGraphicsItem*> item_list = items(x*m_tileWidth,y*m_tileHeight,m_tileWidth,m_tileHeight);

    ///if there is an item write new rect to that Item else create a new Item and set rect
    if (!item_list.isEmpty())
    {
        GraphicsTileItem *gItem = dynamic_cast<GraphicsTileItem *>(item_list.first());
        m_levelScene->setTileSettings(gItem->getIndex(), gItem->getType(), gItem->getRect());
    }

}
