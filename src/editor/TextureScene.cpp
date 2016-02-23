//
// Created by johann on 23.02.16.
//
#include "TextureScene.h"

TextureScene::TextureScene(Settings setting,QPixmap** pixmap, QGraphicsView* View, MainWindow* window) : QGraphicsScene(window) {

    int type=0;


    if (View->objectName().toStdString() == "EnemyView")
    {
        type = 1;
        m_tilesPerRow = 2;
        m_numRows = 10;
        m_tileWidth = 40;
        m_tileHeight = 40;
        std::cout<<"enemy"<<std::endl;
    }
    else if(View->objectName().toStdString() == "TextureView")
    {
        type = 0;
        m_tilesPerRow = 10;
        m_numRows = 4;
        m_tileWidth = 40;
        m_tileHeight = 40;
        std::cout<<"texture"<<std::endl;
    }
    else if(View->objectName().toStdString() == "PlayerView")
    {
        type = 2;
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

    std::cout<<m_textureWidth<<" "<<m_textureHeight<<std::endl;


   for(int i = 0; i < m_textureHeight; i++)
    {
        for(int j = 0; j < m_textureWidth; j++)
        {
            ///puts tile_id in m_tiles
            int tile_id= count-1;
            std::cout<<count<<std::endl;

            ///creates Qrect if m_tiles >=0
            if(tile_id>=0){
                QRect rect((m_tileWidth)*(tile_id%m_tilesPerRow),(m_tileHeight)*((int)(tile_id/m_tilesPerRow)),m_tileWidth,m_tileHeight);
                ///creates new GraphicsTileItem

                GraphicsTileItem *item = new GraphicsTileItem(pixmap,rect,tile_id, type);
                ///sets Position of the rect and adds it to the scene
                item->setPos(m_tileWidth*j,m_tileHeight*i);

                this->addItem(item);
            }
            count++;
        }}
    View->setScene(this);


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
