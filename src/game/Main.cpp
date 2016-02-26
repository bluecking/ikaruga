#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include "MainWindow.hpp"
#include "Game.hpp"
#include "TextureFactory.hpp"
#include "TexturedLayer.hpp"
#include "ScoreBoard.hpp"
#include "Item.hpp"
#include "PuzzleBox.hpp"
#include "LaserWeapon.hpp"

#include "../xml/XML.hpp"

#include <iostream>

using namespace jumper;
using std::string;
using std::cout;
using std::endl;

void getPlayerProperty(XML::Player player, PlayerProperty& p)
{
	int pos_x = player.positionX;
	int pos_y = player.positionY;
	float moveForceX =  player.moveForceX *1.0;
	float moveForceY = player.moveForceY *1.0;
	float maxVelRun = player.maxVel *1.0;

	p.setPosition(Vector2f(pos_x, pos_y));
	p.setMoveForce(Vector2f(moveForceX, moveForceY));
	p.setMaxRunVelocity(maxVelRun);
}

void setupGame(string filename, MainWindow* w, Game* game)
{
	//<alter Teil>
	 std::size_t found = filename.find_last_of("/\\");
	 string path = filename.substr(0,found);
	//</alter Teil>


    //<mein teil>
//    Actor* actor1 =  0;
    //open xml file
    XML xml = XML(filename);


    //create Level
    string xpath = xml.getTileset();
    Level* level = new Level(w->getRenderer(),path +"/" + xpath);
	game->setLevel(level);






    //create Background layer
    XML::Background background  = xml.getBackground();
    xpath                       = background.filename;
    SDL_Texture* texture       = TextureFactory::instance(w->getRenderer()).getTexture(path + "/" + xpath);
    float scrollspeed           = background.scrollspeed * 1.0;
    TexturedLayer* layer       = new TexturedLayer(w->getRenderer(), texture, game->getLevel()->tileHeight());
    layer->setScrollSpeed(scrollspeed);
    game->setLayer(layer);


    XML::Player xplayer  = xml.getPlayer();
    xpath               = xplayer.filename;
    texture       = TextureFactory::instance(w->getRenderer()).getTexture(path + "/" + xpath);
    Player* player = new Player(w->getRenderer(), texture,xplayer.frameWidth, xplayer.frameHeight, xplayer.numFrames);

    // set weapon

    // TODO dynamic weapon attributes
    Vector2i* textureSize = new Vector2i(6, 6);
    Vector2f* weaponOffset = new Vector2f(25, 18.5f);
    Vector2f* projectileColorOffset = new Vector2f(6, 0);
    float coolDown = 0.2f;
    SDL_Texture* weaponTexture = TextureFactory::instance(w->getRenderer()).getTexture(path + "/images/laser_shot.png");
    player->setWeapon(new LaserWeapon(*game, *player, weaponTexture, *textureSize, *weaponOffset, *projectileColorOffset, coolDown));

    game->setPlayer(player);
    player->setFocus(true);

    PlayerProperty p;
    getPlayerProperty(xplayer, p);
    player->setPhysics(p);
    player->setFPS(xplayer.fps);

    float colorOffsetX = xplayer.colorOffsetX;
    float colorOffsetY = xplayer.colorOffsetY;
    Vector2f colorOffset(colorOffsetX, colorOffsetY);
    player->setColorOffset(colorOffset);

    //add bots to level
    game->addBots(xml.getLevelBots());
/*
    //add items
    vector<XML::Item>items = xml.getItems();
    for (auto it = items.begin(); it != items.end(); it++)
    {
        xpath       = (*it).filename;
        texture1    = TextureFactory::instance(w->getRenderer()).getTexture(path + "/" + xpath);
        Item* item  = new Item(w->getRenderer(), texture1,(*it).frameWidth,(*it).frameHeight, 1);
        game->addActor(item);

        actor1 = item;

    }
*/
    //</mein teil>

/*
    //<alter Teil>
	 using boost::property_tree::ptree;
	 ptree pt;
	 read_xml(filename, pt);

	 BOOST_FOREACH(const ptree::value_type&  v, pt.get_child("level") )
	 {
		 if( v.first == "bot" || v.first == "player" || v.first == "item" || v.first == "box")
		 {
			 // Get frame definitions
			 string filename = v.second.get("<xmlattr>.filename", "");
			 int numFrames = v.second.get<int>("numFrames", 0);
			 int frameWidth = v.second.get<int>("frameWidth", 0);
			 int frameHeight = v.second.get<int>("frameHeight", 0);
			 int fps = v.second.get<int>("fps", 14);

			 // Get texture
			 SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(path + "/" + filename);

			 Actor* actor = 0;
			 if(v.first == "bot")
			 {
				// Bot* bot = new Bot(w->getRenderer(), texture, frameWidth, frameHeight, numFrames);
				// game->addActor(bot);
				// actor = bot;
				// actor->setType(ENEMY);
			 }
			 else if(v.first == "player")
			 {
				 Player* player = new Player(w->getRenderer(), texture, frameWidth, frameHeight, numFrames);

                 // set weapon

                 // TODO dynamic weapon attributes
                 Vector2i* textureSize = new Vector2i(6, 6);
                 Vector2f* weaponOffset = new Vector2f(25, 18.5f);
                 Vector2f* projectileColorOffset = new Vector2f(6, 0);
                 float coolDown = 0.2f;
                 SDL_Texture* weaponTexture = TextureFactory::instance(w->getRenderer()).getTexture(path + "/images/laser_shot.png");
                 player->setWeapon(new LaserWeapon(*game, *player, weaponTexture, *textureSize, *weaponOffset, *projectileColorOffset, coolDown));

				 game->setPlayer(player);
				 player->setFocus(true);
				 actor = player;
			 }
			 else if(v.first == "item")
			 {
				 Item* item = new Item(w->getRenderer(), texture, frameWidth, frameHeight, numFrames);
				 game->addActor(item);
				 actor = item;
				 actor->setType(ITEM);
			 }
			 else if(v.first == "box")
			 {
				 PuzzleBox* item = new PuzzleBox(w->getRenderer(), texture, frameWidth, frameHeight, numFrames);
				 game->addActor(item);
				 actor = item;
				 actor->setType(PUZZLEBOX);
			 }

			 // Setup actor properties
			 if(actor)
			 {
				 PlayerProperty p;
				 getPlayerProperty(v, p);
				 actor->setPhysics(p);
				 actor->setFPS(fps);

                 float colorOffsetX = v.second.get<float>("colorOffsetX", 0.0);
                 float colorOffsetY = v.second.get<float>("colorOffsetY", 0.0);
                 Vector2f colorOffset(colorOffsetX, colorOffsetY);
                 actor->setColorOffset(colorOffset);
			 }

		 }
		 if( v.first == "tileset")
		 {
			 string filename = v.second.get("<xmlattr>.filename", "");
			 Level* level = new Level(w->getRenderer(), path + "/" + filename);
			 game->setLevel(level);
		 }
		 if( v.first == "layer")
		 {
			 string filename = v.second.get("<xmlattr>.filename", "");
			 SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(path + "/" + filename);
			 float s = v.second.get<float>("scrollSpeed", 1.0);
			 TexturedLayer* layer = new TexturedLayer(w->getRenderer(), texture, game->getLevel()->tileHeight());
			 layer->setScrollSpeed(s);
			 game->setLayer(layer);
		 }
		 if( v.first == "scoreBoard")
		 {
			 string filename = v.second.get("<xmlattr>.filename", "");
			 SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(path + "/" + filename);
			 int x = v.second.get<int>("xPos", 10);
			 int y = v.second.get<int>("yPos", 10);
			 int dw = v.second.get<int>("digitWidth", 10);
			 int dh = v.second.get<int>("digitHeight", 10);
			 ScoreBoard* board = new ScoreBoard(w->getRenderer(), texture, dw, dh);
			 board->setPosition(Vector2i(x,y));
			 game->setScoreBoard(board);
		 }
 }
*/

    //</alter Teil>
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cout << "Please specify a level to render" << std::endl;
		return -1;
	}

	MainWindow window("Jumper", 625, 576);
	Game game(&window);
	setupGame(argv[1], &window, &game);

	window.setGame(&game);
	game.start();
	window.run();

	// Free textures
	TextureFactory::instance(window.getRenderer()).deleteAll();
}
