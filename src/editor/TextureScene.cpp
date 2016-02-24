//
// Created by johann on 23.02.16.
//
#include "TextureScene.h"

TextureScene::TextureScene(Settings setting,QGraphicsView* View, MainWindow* window) : QGraphicsScene(window) {





    if (View->objectName().toStdString() == "EnemieView")
    {
        m_pixmap=new QPixmap("../res/images/enemys.png");
        m_tilesPerRow = 2;
        m_numRows = 10;
        m_tileWidth = 40;
        m_tileHeight = 40;
        std::cout<<"enemy"<<std::endl;
    }
    else if(View->objectName().toStdString() == "TextureView")
    {
        m_pixmap=new QPixmap("../res/images/rocks.png");
        m_tilesPerRow = 10;
        m_numRows = 4;
        m_tileWidth = 40;
        m_tileHeight = 40;
        std::cout<<"texture"<<std::endl;
    }
    else if(View->objectName().toStdString() == "PlayerView")
    {
        m_pixmap=new QPixmap("../res/images/player.png");
        m_tilesPerRow = 2;
        m_numRows = 1;
        m_tileWidth = 40;
        m_tileHeight = 80;
        std::cout<<"player"<<std::endl;
    }


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
            std::cout<<count<<std::endl;

            ///creates Qrect if m_tiles >=0
            if(tile_id>=0){
                QRect rect(0,0,m_tileWidth,m_tileHeight);
                ///creates new GraphicsTileItem

                GraphicsTileItem *item = new GraphicsTileItem(m_pixmap,rect,tile_id);
                ///sets Position of the rect and adds it to the scene
                item->setPos(0,0);

                std::cout<<count<<std::endl;
                this->addItem(item);
            }
            count++;
        }}



}

QGraphicsScene* TextureScene::getScene()
{
    return this;
}


void TextureScene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsItem *item;
    item = itemAt(event->scenePos()); //Get the item at the position
    GraphicsTileItem *gItem=dynamic_cast<GraphicsTileItem*>(item);
    if (item) //If there is an item at that position
    {
        std::cout<<gItem->getIndex()<<std::endl;
    }
}
