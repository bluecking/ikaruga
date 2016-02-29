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
    m_typeItem=2;
    m_typeBot=1;
    m_typeTexture=0;

    loadXml(filename);

    m_bots =m_xml->getBots();
    m_items=m_xml->getItems();
    m_weapons=m_xml->getWeapons();
    m_bot  =m_bots[0];
    m_item =m_items[0];
    m_weapon=m_weapons[0];
	m_mainWindow=window;
	m_setting=Settings();
    m_fileName=filename;
    m_scrollSpeed=0.9;
    m_color="black";
    m_imgTexture="../images/rocks.png";
    m_imgBackground="../images/star_background_2_200x200.png";
    m_imgStatusbar="../images/statusbar_font_10x10.png";
    m_imgPlayer="../images/player_animated_55x43_transparent.png";



    int last = (filename.lastIndexOf("/"));
    m_path = filename.mid(0, last + 1);

    int lastName=filename.lastIndexOf(".");
    m_levelName=filename.mid(last+1,lastName-last-1);
    m_levelName=m_levelName+".lvl";


    m_background.filename     =m_imgBackground.toStdString();
    m_background.scrollspeed  =m_scrollSpeed;

    m_statusbar.filename      =m_imgStatusbar.toStdString();
    m_statusbar.capitalOffset =1;
    m_statusbar.frameHeight   =10;
    m_statusbar.frameWidth    =10;
    m_statusbar.letterCount   =26;
    m_statusbar.minusculeOffset=2;
    m_statusbar.numberOffset  =0;
    m_statusbar.offsetToMid   =1;

    m_player.frameWidth       =55;
    m_player.frameHeight      =43;
    m_player.colorOffsetX     =1320;
    m_player.colorOffsetY     =0;
    m_player.filename         =m_imgPlayer.toStdString();
    m_player.fps              =12;
    m_player.maxVel           =200;
    m_player.moveForceX       =200;
    m_player.moveForceY       =200;
    m_player.numFrames        =24;
    m_player.positionX        =100;
    m_player.positionY        =100;
    m_player.stdWeapon        =m_weapon  ;




    loadLevel(m_levelName);

    for(unsigned int i=0;i<m_bots.size();i++)
    {
        m_mainWindow->addBot(toQString(m_bots[i].type),
        "Texture name: \t\t"+toQString(m_bots[i].filename)+"\n"+
        "Health: \t\t"+toQString(std::to_string(m_bots[i].health))+"\n"+
        "Type: \t\t"+toQString(m_bots[i].npc.type)+"\n"+
        "Std Weapon: \t\t"+toQString(m_bots[i].npc.stdWeapon)+"\n"+
        "Move function: \t\t"+toQString(m_bots[i].npc.move_function)+"\n"+
        "Move Value: \t\t"+toQString(std::to_string(m_bots[i].npc.move_value))+"\n"+
        "Speed: \t\t"+toQString(std::to_string(m_bots[i].npc.speed))
        );

    }

    for(unsigned int i=0;i<m_items.size();i++)
    {
        m_mainWindow->addPower(toQString(m_items[i].type),
        "Texture name: \t\t"+toQString(m_items[i].filename)
        );

    }

	///Create TextureViews
	TextureScene* m_textureView= new TextureScene(m_setting,window->ui->TextureView,this, window);

	///sets MainViewScene
    window->ui->MainView->setScene(this);

	///set the TextureViews to VisibleS
	window->ui->TextureView->setScene(m_textureView);

    //saveXml(filename);


}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent * event) {

	///Calculates Clickposition and the containing Items

    int x = event->scenePos().x()/m_tileWidth;
	int y = event->scenePos().y()/m_tileHeight;
    QList<QGraphicsItem*> item_list = items(x*m_tileWidth,y*m_tileHeight,m_tileWidth,m_tileHeight);


    if(!item_list.empty()) {
        if ((dynamic_cast<GraphicsTileItem *>(item_list.first()))->getType() == 1) {
            std::cout << "remove Bot" << std::endl;
            m_tiles[y][x] = -1;
            for (unsigned int i = 0; i < m_levelBots.size(); i++) {
                if (m_levelBots[i].positionX == x * m_tileWidth && m_levelBots[i].positionY == y * m_tileWidth) {
                    if (event->buttons() == Qt::LeftButton) {
                        m_color = m_levelBots[i].color;
                        if (m_color == "black")m_color = "white";
                        else m_color = "black";

                    }
                    m_levelBots.erase(m_levelBots.begin() + i);
                }
            }
        }

        if ((dynamic_cast<GraphicsTileItem *>(item_list.first()))->getType() == 2) {
            std::cout << "remove Item" << std::endl;
            m_tiles[y][x] = -1;
            for (unsigned int i = 0; i < m_levelItems.size(); i++) {
                if (m_levelItems[i].positionX == x * m_tileWidth && m_levelItems[i].positionY == y * m_tileWidth) {
                    m_levelItems.erase(m_levelItems.begin() + i);
                }
            }
        }
    }


    if(event->buttons() == Qt::LeftButton)

    {
	///if there is an item write new rect to that Item else create a new Item and set rect
	if (!item_list.isEmpty())
	{



        if(!m_bot.filename.empty())
        {
            if(m_color=="white")
            {
                QRect rect(0,0, m_bot.frameWidth, m_bot.frameHeight);
                m_rect=rect;

            }
            else
            {
                QRect rect(m_bot.colorOffsetX,m_bot.colorOffsetY, m_bot.frameWidth, m_bot.frameHeight);
                m_rect=rect;
            }

            QPixmap* map =new QPixmap(toQString(m_path.toStdString()+m_bot.filename));
            (dynamic_cast<GraphicsTileItem *>(item_list.first()))->changeItem(map, m_rect,m_typeBot);

            m_tiles[y][x]=-1;
            std::cout<<"bot added"<<std::endl;
            XML::LevelBot bot;

            bot.color=m_color;
            bot.positionX = x*m_tileWidth;
            bot.positionY = y*m_tileHeight;
            bot.powerUpName="HealtBoost";
            bot.powerUpProb=0.05;
            bot.type=m_bot;
            m_levelBots.push_back(bot);
        }
        else if(!m_item.filename.empty())
        {

            QRect rect(0,0, m_item.frameWidth, m_item.frameHeight);
            m_rect=rect;

            std::cout<<"item added"<<std::endl;
            m_tiles[y][x]=-1;
            QPixmap* map =new QPixmap(toQString(m_path.toStdString()+m_item.filename));
            (dynamic_cast<GraphicsTileItem *>(item_list.first()))->changeItem(map, m_rect, m_typeItem);

            XML::LevelItem item;
            item.positionX= x*m_tileWidth;
            item.positionY= y*m_tileHeight;
            item.type =m_item.type;

        }
        else
        {
            (dynamic_cast<GraphicsTileItem *>(item_list.first()))->changeItem(m_type, m_rect,m_index);
            m_tiles[y][x]=m_index;
            setNull();
        }
		m_mainWindow->ui->MainView->setScene(this);
	}
	else
	{

		///creates a new Item and update View
		GraphicsTileItem *item = new GraphicsTileItem(m_pixmap,m_rect,m_index,m_type);

        if(!m_bot.filename.empty())
        {
            m_item.filename.clear();
            if(m_color=="white")
            {
                QRect rect(0,0, m_bot.frameWidth, m_bot.frameHeight);
                m_rect=rect;

            }
            else
            {
                QRect rect(m_bot.colorOffsetX,m_bot.colorOffsetY, m_bot.frameWidth, m_bot.frameHeight);
                m_rect=rect;
            }

            QPixmap* map =new QPixmap(toQString(m_path.toStdString()+m_bot.filename));
            item->changeItem(map, m_rect, m_typeBot);

            m_tiles[y][x]=-1;
            std::cout<<"bot added"<<std::endl;
            XML::LevelBot bot;

            bot.color = m_color;
            bot.positionX = x*m_tileWidth;
            bot.positionY = y*m_tileHeight;
            bot.powerUpName="HealtBoost";
            bot.powerUpProb=0.05;
            bot.type=m_bot;
            m_levelBots.push_back(bot);
        }
        else if(!m_item.filename.empty())
        {
            m_bot.filename.clear();
            QRect rect(0,0, m_item.frameWidth, m_item.frameHeight);
            m_rect=rect;

            std::cout<<"item added"<<std::endl;
            m_tiles[y][x]=-1;
            QPixmap* map =new QPixmap(toQString(m_path.toStdString()+m_item.filename));
            item->changeItem(map, m_rect,m_typeItem);

            XML::LevelItem item;
            item.positionX= x*m_tileWidth;
            item.positionY= y*m_tileHeight;
            item.type =m_item.type;

        }
        else
        {
            setNull();
            m_tiles[y][x]=m_index;
        }
        m_mainWindow->ui->MainView->setScene(this);

		item->setPos(m_tileWidth*x,m_tileHeight*y);
		this->addItem(item);
		m_mainWindow->ui->MainView->setScene(this);
	}}

    else if(!item_list.isEmpty() && event->button()==Qt::RightButton)
    {


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

    if(QFile(fileName).exists()) {

        std::cout << fileName.toStdString() << std::endl;
        m_xml = new XML(fileName.toStdString());



        m_levelName = toQString(m_xml->getTileset());
        m_xmlFileName = toQString(m_xml->getFilename());
        m_bots = m_xml->getBots();
        m_levelId = m_xml->getId();


        m_levelBots = m_xml->getLevelBots();
    }
    else
    {
        m_xml = new XML();
        m_xml->setFilename(fileName.toStdString());
        m_xml->save();
        m_xml = new XML(fileName.toStdString());
    }

}

QString LevelScene::toQString(std::string string)
{
    return QString::fromUtf8(string.c_str());
}

void LevelScene::saveXml(QString fileName)
{


    m_xml->setFilename(fileName.toStdString());
    m_xml->setTileset(m_levelName.toStdString());
    m_xml->setLevelname("Milky test");
    m_xml->setId(1);
    m_xml->setLevelBots(m_levelBots);
    m_xml->setBackground(m_background);
    m_xml->setStatusbar(m_statusbar);
    m_xml->setPlayer(m_player);

    m_xml->save();


    saveLevel(m_levelName);

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
    QFile file(m_path+fileName);

    std::cout<<m_path.toStdString()+fileName.toStdString()<<std::endl;
    ///readonly file open
    if(file.open(QIODevice::ReadOnly)) {

        QTextStream in(&file);

        ///Filename
        QString line = in.readLine();


        m_pixmap = new QPixmap *[6];
        std::cout << m_path.toStdString() << "../images/rocks.png" << std::endl;

        m_pixmap[0] = new QPixmap(m_path + m_imgTexture);
        m_pixmap[1] = new QPixmap(m_path + "../images/Bot_1.png");
        m_pixmap[2] = new QPixmap(m_path + "../images/Bot_2.png");
        m_pixmap[3] = new QPixmap(m_path + "../images/Bot_3.png");
        m_pixmap[4] = new QPixmap(m_path + "../images/Bot_4.png");
        m_pixmap[5] = new QPixmap(m_path + "../images/Bot_5.png");
        ///m_pixmap[1]= new QPixmap(m_path+"../images/bot_1");



        ///list that contains all values
        QStringList list;

        ///lvl properties
        line = in.readLine();
        list = line.split(" ");
        m_tileWidth = list[0].toInt();
        m_tileHeight = list[1].toInt();
        m_tilesPerRow = list[2].toInt();
        m_numRows = list[3].toInt();
        m_tileOffset = list[4].toInt();
        m_levelWidth = list[5].toInt();
        m_levelHeight = 14;


        setTileSettings(0, 0, QRect(0, 0, 40, 40));



        ///sets Labels of the Gui
        m_mainWindow->ui->spinBox->setValue(m_levelWidth);




        // Alloc tile set memory
        m_tiles = new std::vector<int>[m_levelHeight];



        // Read tile indices
        for (int i = 0; i < m_levelHeight; i++) {

            line = in.readLine();
            list = line.split(" ");
            if (list.length() == m_levelWidth) {
                for (int j = 0; j < m_levelWidth; j++) {


                    ///puts tile_id in m_tiles
                    m_tiles[i].push_back(list[j].toInt() - 1);

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

        for (int i = 0; i < m_levelBots.size(); i++) {

            QList<QGraphicsItem*> item_list = items(m_levelBots[i].positionX,m_levelBots[i].positionY,
                                                    m_levelBots[i].type.frameWidth,m_levelBots[i].type.frameHeight);
            if(item_list.empty())
            {
            if (m_levelBots[i].color == "white")
            {
                QRect rect(0, 0, m_levelBots[i].type.frameWidth, m_levelBots[i].type.frameHeight);
                m_rect = rect;

            }
            else {
                QRect rect(m_levelBots[i].type.colorOffsetX, m_levelBots[i].type.colorOffsetY, m_levelBots[i].type.frameWidth, m_levelBots[i].type.frameHeight);
                m_rect = rect;
            }

                QPixmap* map = new QPixmap(toQString(m_path.toStdString() + m_levelBots[i].type.filename));
                GraphicsTileItem *item = new GraphicsTileItem(map, m_rect, 0, m_typeBot);
                item->setPos(m_levelBots[i].positionX, m_levelBots[i].positionY);
                this->addItem(item);


            }
            else
            {
                std::cout<<"Failed to load bot"<<std::endl;
            }
        }


    }

    else
    {
        m_tiles = new std::vector<int>[m_levelHeight];

        for(int i=0;i<m_levelHeight;i++)
        {
            for(int j=0;j<m_levelWidth;j++)
            {
                if(i==0)m_tiles[i].push_back(7);
                else if(i<m_levelHeight-1)m_tiles[i].push_back(-1);
                if(i==m_levelHeight-1)m_tiles[i].push_back(0);
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

    QFile readfile(m_path+fileName);
    QTextStream write(&readfile);
    if(readfile.open(QFile::WriteOnly  | QFile::Text))
    {
            write<<m_imgTexture<<"\n";

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

void LevelScene::setSize(int value)
{
    if(value<m_levelWidth)
    {
        QList<QGraphicsItem*> item_list = items(value*m_tileWidth,0,m_tileWidth*(m_levelWidth-value),m_tileHeight*m_levelHeight);
        while(!item_list.isEmpty())
        {
            this->removeItem(item_list.first());
            delete item_list.first();
            item_list.removeFirst();

        }

        for(int i=0;i<m_levelHeight;i++)
        {
            for(int j=value;j<m_levelWidth;j++)
            {
                m_tiles[i].pop_back();
            }
        }
    }

    else
    {
        for(int i=0;i<m_levelHeight;i++)
        {
            for(int j=m_levelWidth;j<value;j++)
            {
                if(i==0)m_tiles[i].push_back(7);
                else if(i<m_levelHeight-1)m_tiles[i].push_back(-1);
                if(i==m_levelHeight-1)m_tiles[i].push_back(0);

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
    m_mainWindow->ui->MainView->setScene(this);
    m_mainWindow->ui->MainView->showMinimized();
    m_levelWidth=value;
}

void LevelScene::setBot(QString botName)
{
    for(unsigned int i=0;i<m_bots.size();i++)
    {
        if(m_bots[i].type==botName.toStdString())
        {
            m_bot=m_bots[i];
        }
    }
    m_item.filename.clear();
}

void LevelScene::setPower(QString powerName)
{
    for(unsigned int i=0;i<m_items.size();i++)
    {
        if(m_items[i].type==powerName.toStdString())
        {
            m_item=m_items[i];
        }
    }
    m_bot.filename.clear();
}

void LevelScene::setNull()
{
    m_bot.filename.clear();
    m_item.filename.clear();
}
