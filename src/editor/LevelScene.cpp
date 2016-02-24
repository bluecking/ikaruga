#include"LevelScene.hpp"


LevelScene::LevelScene(QString filename, MainWindow* window) : QGraphicsScene(window)
{
//Set all default values
	m_tileWidth 	= 0;
	m_tileHeight	= 0;
	m_tileOffset 	= 0;
	m_numRows = 0;
	m_keyR = 0;
	m_keyG = 0;
	m_keyB = 0;
	m_tilesPerRow = 0;
	m_levelWidth = 0;
	m_levelHeight = 0;
	m_mainWindow=window;
	m_setting=Settings();


	// Read meta data from level file
	QFile file(filename);
	

	///int for rgb colors
	int ir, ig, ib;

	///readonly file open
	if(file.open(QIODevice::ReadOnly))
	{

	  
	  QTextStream in(&file);
	  
          ///Filename  
	  QString line = in.readLine();
		int last=(filename.lastIndexOf("/"));
	  QString tmp;
	  tmp=filename.mid(0,last)+line;
	  m_texFileName=tmp.toStdString();
	  std::cout<<(filename.mid(0,last+1)+line).toStdString()<<std::endl;

		m_pixmap=new QPixmap*[5];

		QString string=filename.mid(0,last+1)+"rocks.png";

		m_pixmap[0]= new QPixmap(filename.mid(0,last+1)+line);
		m_pixmap[1]= new QPixmap(string);
		m_pixmap[2]= new QPixmap(filename.mid(0,last+1)+"enemys.png");
		m_pixmap[3]= new QPixmap(filename.mid(0,last+1)+"player.png");

		std::cout<<string.toStdString()<<std::endl;




	  QStringList list;

          ///lvl properties
          line           =in.readLine();
	  list           =line.split(" ");
          m_tileWidth    =list[0].toInt();
          m_tileHeight   =list[1].toInt();
          m_tilesPerRow  =list[2].toInt();
          m_numRows      =list[3].toInt();
          m_tileOffset   =list[4].toInt();
          ir             =list[5].toInt();
          ig             =list[6].toInt();
          ib             =list[7].toInt();
          m_levelWidth   =list[8].toInt();
          m_levelHeight  =list[9].toInt();


	///window->tile_width->setText(QString::number(m_tileWidth));
	///window->tile_height->setText(QString::number(m_tileHeight));
	window->level_width->setText(QString::number(m_levelWidth));
	window->level_height->setText(QString::number(m_levelHeight));



		// Alloc tile set memory
		m_tiles = new int*[m_levelHeight];
		for(int i = 0; i < m_levelHeight; i++)
		{
			m_tiles[i] = new int[m_levelWidth];
		}


		int count=0;
		line = in.readLine();
		list = line.split(" ");
		// Read tile indices
		for(int i = 0; i < m_levelHeight; i++)
		{
			for(int j = 0; j < m_levelWidth; j++)
			{
				///puts tile_id in m_tiles
				m_tiles[i][j] = list[count].toInt()-1;
				///creates Qrect if m_tiles >=0
				if(m_tiles[i][j]>=0){
					QRect rect((m_tileWidth)*(m_tiles[i][j]%m_tilesPerRow),(m_tileHeight)*((int)(m_tiles[i][j]/m_tilesPerRow)),m_tileWidth,m_tileHeight);
					///creates new GraphicsTileItem
					GraphicsTileItem *item = new GraphicsTileItem(m_pixmap,rect,m_tiles[i][j],0);
					///sets Position of the rect and adds it to the scene
					item->setPos(m_tileWidth*j,m_tileHeight*i);
					this->addItem(item);
				}
				count++;
			}
		}


	}

	else
	{
		std::cout << "Unable to open file " << std::endl;
	}
	
	//Cast keying colors manually!
	m_keyR = (unsigned char)ir;
	m_keyG = (unsigned char)ib;
	m_keyB = (unsigned char)ig;

	///file close
	file.close();
	///sets Scene
	window->MainView->setScene(this);

	TextureScene* m_textureView= new TextureScene(m_setting,window->TextureView,this, window);
	TextureScene* m_enemyView= new TextureScene(m_setting,window->EnemieView,this, window);
    TextureScene* m_playerView= new TextureScene(m_setting,window->PlayerView,this, window);
	window->TextureView->setScene(m_textureView);
	window->EnemieView->setScene(m_enemyView);
	window->PlayerView->setScene(m_playerView);






}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent * event) {
	QGraphicsItem *item;
	item = itemAt(event->scenePos()); //Get the item at the position
	int x = event->scenePos().x()/m_tileWidth;
	int y = event->scenePos().y()/m_tileHeight;
	QList<QGraphicsItem*> item_list = items(x*m_tileWidth,y*m_tileHeight,m_tileWidth,m_tileHeight);
	GraphicsTileItem *gItem = dynamic_cast<GraphicsTileItem *>(item);

	std::cout << x << " " << y << std::endl;
	if (!item_list.isEmpty()) //If there is an item at that position
	{
		(dynamic_cast<GraphicsTileItem *>(item_list.first()))->changeItem(m_type, m_rect, m_index);
		m_mainWindow->MainView->setScene(this);
	}
	else
	{
		GraphicsTileItem *item = new GraphicsTileItem(m_pixmap,m_rect,m_index,m_type);
		m_tiles[y][x]=m_index;
		item->setPos(m_tileWidth*x,m_tileHeight*y);
		this->addItem(item);
		m_mainWindow->MainView->setScene(this);
	}
}

void LevelScene::setTileSettings(int index,int type, QRect rect)
{
	m_index=index;
	m_type =type;
	m_rect =rect;
}
