#include"LevelScene.hpp"




LevelScene::LevelScene(QString filename, MainWindow* window) : QGraphicsScene(window)
{

	//Set all default values
	m_tileWidth 	= 40;
	m_tileHeight	= 40;
	m_tileOffset 	= 0;
	m_numRows = 4;
	m_tilesPerRow = 10;
	m_levelWidth = 400;
	m_levelHeight = 14;
    m_texFileName="../images/rocks.png";
	m_mainWindow=window;
	m_setting=Settings();
    m_fileName=filename;


    loadXml(filename);

    loadLevel(m_levelName);

	///Create TextureViews
	TextureScene* m_textureView= new TextureScene(m_setting,window->ui->TextureView,this, window);
	TextureScene* m_enemyView= new TextureScene(m_setting,window->ui->EnemieView,this, window);

	///sets MainViewScene
    window->ui->MainView->setScene(this);
    
	///set the TextureViews to VisibleS
	window->ui->TextureView->setScene(m_textureView);
	window->ui->EnemieView->setScene(m_enemyView);

    saveXml(filename);


}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent * event) {

	///Calculates Clickposition and the containing Items

    int x = event->scenePos().x()/m_tileWidth;
	int y = event->scenePos().y()/m_tileHeight;
    QList<QGraphicsItem*> item_list = items(x*m_tileWidth,y*m_tileHeight,m_tileWidth,m_tileHeight);


    if(event->buttons() == Qt::LeftButton)

    {
	///if there is an item write new rect to that Item else create a new Item and set rect
	if (!item_list.isEmpty())
	{
		(dynamic_cast<GraphicsTileItem *>(item_list.first()))->changeItem(m_type, m_rect, m_index);
        if(m_type==0)
        {
            m_tiles[y][x]=m_index;
        }
        else
        {

            XML::LevelBot bot;

            if(m_index<1)bot.color=1;
            else bot.color=2;
            bot.positionX = x;
            bot.positionY = y;
            bot.powerUpName="HealtBoost";
            bot.powerUpProb=0.05;


            m_bots.push_back(bot);
            ///bot.type=atoi(mtype);
        }
		m_mainWindow->ui->MainView->setScene(this);
	}
	else
	{
		///creates a new Item and update View
		GraphicsTileItem *item = new GraphicsTileItem(m_pixmap,m_rect,m_index,m_type);
		m_tiles[y][x]=m_index;
		item->setPos(m_tileWidth*x,m_tileHeight*y);
		this->addItem(item);
		m_mainWindow->ui->MainView->setScene(this);
	}}

    else if(!item_list.isEmpty() && event->button()==Qt::RightButton)
    {
        m_tiles[y][x]=-1;
        this->removeItem(item_list.first());
        m_mainWindow->ui->MainView->setScene(this);
        delete item_list.first();
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

void LevelScene::loadXml(QString fileName)
{

    m_xml = new XML(fileName.toStdString());

    int last=(fileName.lastIndexOf("/"));

    m_path=fileName.mid(0,last+1);

    m_levelName     = toQString(m_xml->getTileset());
    m_levelName     =m_path+m_levelName;
    m_xmlFileName   =toQString(m_xml->getFilename());
    m_levelId       =m_xml->getId();
    std::cout<<"foo"<<std::endl;

    std::vector<XML::LevelBot>  bots = m_xml->getLevelBots();


}

QString LevelScene::toQString(std::string string)
{
    return QString::fromUtf8(string.c_str());
}

void LevelScene::saveXml(QString fileName)
{


    m_xml = new XML();

    m_xml->setFilename(m_path.toStdString()+"testFile.xml");
    m_xml->setTileset(m_levelName.toStdString());
    m_xml->setLevelname("Milky test");
    m_xml->setId(1);
    m_xml->setLevelBots(m_bots);
    m_xml->save();

    saveLevel(m_path+"test_collision.lvl");

    /**m_xml->setLevelBot();
    m_xml->setTileset()
    m_xml->setBackground();
    m_xml->setFilename();
    m_xml->setId();
    m_xml->setLevelBots();
    m_xml->setLevelItems():
    m_xml->setLevelItem();
    m_xml->setLevelname();
    m_xml->setPlayer();
    m_xml->setLevelname();*/

}



void LevelScene::loadLevel(QString fileName )
{
    // Read meta data from level file
    QFile file(fileName);
    ///readonly file open
    if(file.open(QIODevice::ReadOnly))
    {

        QTextStream in(&file);

        ///Filename
        QString line = in.readLine();



        m_pixmap=new QPixmap*[6];
        std::cout<<m_path.toStdString()<<"../images/rocks.png"<<std::endl;

        m_pixmap[0]= new QPixmap(m_path+m_texFileName);
        m_pixmap[1]= new QPixmap(m_path+"../images/Bot_1.png");
        m_pixmap[2]= new QPixmap(m_path+"../images/Bot_2.png");
        m_pixmap[3]= new QPixmap(m_path+"../images/Bot_3.png");
        m_pixmap[4]= new QPixmap(m_path+"../images/Bot_4.png");
        m_pixmap[5]= new QPixmap(m_path+"../images/Bot_5.png");
        ///m_pixmap[1]= new QPixmap(m_path+"../images/bot_1");



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


        setTileSettings(0,0,QRect(0,0,40,40));



        ///sets Labels of the Gui
        m_mainWindow->ui->spinBox->setValue(m_levelWidth);




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
        ///file close
        file.close();


    }

    else
    {
        m_tiles = new int*[m_levelHeight];
        for(int i = 0; i < m_levelHeight; i++)
        {
            m_tiles[i] = new int[m_levelWidth];
        }

        for(int i=0;i<m_levelHeight;i++)
        {
            for(int j=0;j<m_levelWidth;j++)
            {
                if(i==0)m_tiles[i][j]=7;
                else if(i<m_levelHeight-1)m_tiles[i][j]=-1;
                if(i==m_levelHeight-1)m_tiles[i][j]=0;
            }
        }
        ///file close
        file.close();
        saveLevel(m_levelName);
        loadLevel(fileName);

    }




}



void LevelScene::saveLevel(QString fileName)
{

    QFile readfile(fileName);
    QTextStream write(&readfile);
    if(readfile.open(QFile::WriteOnly  | QFile::Text))
    {
            write<<m_texFileName<<"\n";

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
                    if(j!=m_levelWidth-1) write<<m_tiles[i][j]+1<<" ";
                    else write<<m_tiles[i][j]+1;

                }
            write<<"\n";
        }

        readfile.close();
    }
}


