#include"LevelScene.hpp"


LevelScene::LevelScene(QString filename, MainWindow* window) : QGraphicsScene(window)
{

	//Set all default values
	m_tileWidth 	= 0;
	m_tileHeight	= 0;
	m_tileOffset 	= 0;
	m_numRows = 0;
	m_tilesPerRow = 0;
	m_levelWidth = 0;
	m_levelHeight = 0;
	m_mainWindow=window;
	m_setting=Settings();
    m_fileName=filename;



	// Read meta data from level file
	QFile file(m_fileName);
	

	///int for rgb colors


	///readonly file open
	if(file.open(QIODevice::ReadOnly))
	{

	  	QTextStream in(&file);
	  
    	///Filename
		QString line = in.readLine();
	  	int last=(filename.lastIndexOf("/"));
	  	m_pfad=filename.mid(0,last+1);
	  	m_texFileName=m_pfad+line;
        m_enemyFileName=m_pfad+"images/enemys.png";

	  	std::cout<<(filename.mid(0,last+1)+line).toStdString()<<std::endl;


		m_pixmap=new QPixmap*[6];

		m_pixmap[0]= new QPixmap(m_pfad+"../images/rocks.png");
		///m_pixmap[1]= new QPixmap(m_pfad+"../images/bot_1");



		///list that contains all values
	  	QStringList list;

		///lvl properties
		line           =in.readLine();
	  	list           =line.split(" ");
        m_tileWidth    =list[0].toInt();
        m_tileHeight   =list[1].toInt();
        m_tilesPerRow  =list[2].toInt();
        m_numRows      =list[3].toInt();
        m_tileOffset   =list[4].toInt();
        m_levelWidth   =list[5].toInt();
		m_levelHeight  =14;



		///sets Labels of the Gui
		///window->level_width->setText(QString::number(m_levelWidth));
		///window->level_height->setText(QString::number(m_levelHeight));



		// Alloc tile set memory
		m_tiles = new int*[m_levelHeight];
		for(int i = 0; i < m_levelHeight; i++)
		{
			m_tiles[i] = new int[m_levelWidth];
		}




		// Read tile indices
		for(int i = 0; i < m_levelHeight; i++) {
            line = in.readLine();
            list = line.split(" ");
            if (list.length() == m_levelWidth)
            {
                for (int j = 0; j < m_levelWidth; j++) {


                    ///puts tile_id in m_tiles
                    m_tiles[i][j] = list[j].toInt() - 1;

                    ///creates Qrect if m_tiles >=0
                    if (m_tiles[i][j] >= 0) {
                        ///Creates Rect for GraphicsTileItem
                        QRect rect((m_tileWidth) * (m_tiles[i][j] % m_tilesPerRow),
                                   (m_tileHeight) * ((int) (m_tiles[i][j] / m_tilesPerRow)), m_tileWidth, m_tileHeight);

                        ///creates new GraphicsTileItem
                        GraphicsTileItem *item = new GraphicsTileItem(m_pixmap, rect, m_tiles[i][j], 0);

                        ///sets Position of the rect and adds it to the scene
                        item->setPos(m_tileWidth * j, m_tileHeight * i);
                        this->addItem(item);
                    }
                }
            }
        }

	}

	else
	{
		std::cout << "Unable to open file " << std::endl;
	}


	///file close
	file.close();

	///Create TextureViews
	TextureScene* m_textureView= new TextureScene(m_setting,window->TextureView,this, window);
	///TextureScene* m_enemyView= new TextureScene(m_setting,window->EnemieView,this, window);
    ///TextureScene* m_playerView= new TextureScene(m_setting,window->PlayerView,this, window);

	///sets MainViewScene
	window->MainView->setScene(this);

	///set the TextureViews to Visible
	window->TextureView->setScene(m_textureView);
	///window->EnemieView->setScene(m_enemyView);
	///window->PlayerView->setScene(m_playerView);

}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent * event) {

	///Calculates Clickposition and the containing Items
	int x = event->scenePos().x()/m_tileWidth;
	int y = event->scenePos().y()/m_tileHeight;
	QList<QGraphicsItem*> item_list = items(x*m_tileWidth,y*m_tileHeight,m_tileWidth,m_tileHeight);

	///if there is an item write new rect to that Item else create a new Item and set rect
	if (!item_list.isEmpty())
	{
		(dynamic_cast<GraphicsTileItem *>(item_list.first()))->changeItem(m_type, m_rect, m_index);
		m_mainWindow->MainView->setScene(this);
	}
	else
	{
		///creates a new Item and update View
		GraphicsTileItem *item = new GraphicsTileItem(m_pixmap,m_rect,m_index,m_type);
		m_tiles[y][x]=m_index;
		item->setPos(m_tileWidth*x,m_tileHeight*y);
		this->addItem(item);
		m_mainWindow->MainView->setScene(this);
	}
}

QPixmap** LevelScene::getPixmap()
{
	return m_pixmap;
}

void LevelScene::setTileSettings(int index,int type, QRect rect)
{
	///sets textureType
	m_index=index;
	m_type =type;
	m_rect =rect;
}

void LevelScene::saveLevel(QString fileName)
{

    QFile readfile(fileName+"editor.lvl");
    QTextStream write(&readfile);
    if(readfile.open(QFile::WriteOnly  | QFile::Text))
    {
            write<<"../images/rocks.png"<<"\n";

            write<<m_tileWidth<<" ";
            write<< m_tileHeight<<" ";
            write<<m_tilesPerRow<<" ";
            write<<m_numRows<<" ";
            write<<m_tileOffset<<" ";
            write<<m_levelWidth<<"\n";

        for(int i = 0; i < m_levelHeight; i++)
        {
                for (int j = 0; j < m_levelWidth; j++) {

                    ///puts tile_id in m_tiles
                    write<<m_tiles[i][j]+1<<" ";

                }
            write<<"\n";
        }

        readfile.close();
    }
}

void LevelScene::saveXml(QString fileName)
{

}
