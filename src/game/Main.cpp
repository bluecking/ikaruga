#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include "MainWindow.hpp"
#include "Game.hpp"
#include "TextureFactory.hpp"
#include "TexturedLayer.hpp"
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
    float moveForceX = player.moveForceX * 1.0;
    float moveForceY = player.moveForceY * 1.0;
    float maxVelRun = player.maxVel * 1.0;

    p.setPosition(Vector2f(pos_x, pos_y));
    p.setMoveForce(Vector2f(moveForceX, moveForceY));
    p.setMaxRunVelocity(maxVelRun);
}


void getBotProperty(XML::LevelBot bot, PlayerProperty& p)
{
    int pos_x = bot.positionX;
    int pos_y = bot.positionY;
    float moveForceX = 1.0;
    float moveForceY = 1.0;
    float maxVelRun = 1.0;

    p.setPosition(Vector2f(pos_x, pos_y));
    p.setMoveForce(Vector2f(moveForceX, moveForceY));
    p.setMaxRunVelocity(maxVelRun);
}

//create level
void setupLevel(MainWindow* w,Game* game,std::string filepath)
{
    Level* level = new Level(w->getRenderer(), filepath);
    game->setLevel(level);
}

//Creates the Levelbackground
void setupBackground(XML::Background background,std::string filepath,MainWindow* w,Game* game)
{

    SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(filepath);
    float scrollspeed = background.scrollspeed * 1.0;
    TexturedLayer* layer = new TexturedLayer(w->getRenderer(), texture, game->getLevel()->tileHeight());
    layer->setScrollSpeed(scrollspeed);
    game->setLayer(layer);
}

//create statusbar
void setupStatusbar(MainWindow* w, Game* game ,XML::Statusbar statusbar, std::string filepath)
{
    SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(filepath);

    StatusBar * bar = new StatusBar(w->getRenderer(), texture, statusbar.frameWidth, statusbar.frameHeight, statusbar.capitalOffset,
                                    statusbar.minusculeOffset,statusbar.numberOffset, statusbar.letterCount, statusbar.offsetToMid);


    int yStart = w->h() - (game->getLevel()->levelHeight() * game->getLevel()->tileHeight());

    int xEnd = w->w()-1;
    bar->setPosition(Vector2i(0, yStart), Vector2i(xEnd, 0));
    game->setStatusBar(bar);



}
//create Player
void setupPlayer(XML::Player xplayer,MainWindow* w,Game* game,std::string filepath)
{

    SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(filepath+"/"+xplayer.filename);
    Player* player = new Player(w->getRenderer(), texture, xplayer.frameWidth, xplayer.frameHeight, xplayer.numFrames);

    // set weapon

    // TODO dynamic weapon attributes

    Vector2i* textureSize = new Vector2i(6, 6);
    Vector2f* weaponOffset = new Vector2f(25, 18.5f);
    Vector2f* projectileColorOffset = new Vector2f(6, 0);
    float coolDown = 0.2f;
    SDL_Texture* weaponTexture = TextureFactory::instance(w->getRenderer()).getTexture(
            filepath + "/../images/laser_shot.png");
    player->setWeapon(
            new LaserWeapon(*game, *player, weaponTexture, *textureSize, *weaponOffset, *projectileColorOffset,

                            coolDown));


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
}

//create Bots
void setupBots(vector<XML::LevelBot>bots,MainWindow* w,Game* game,std::string filepath)
{
    for (auto it = begin(bots); it != end(bots); it++)
    {


        SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(filepath+"/"+(*it).type.filename);

        Bot* bot = new Bot(w->getRenderer(), texture, (*it).type.frameWidth, (*it).type.frameHeight,
                           (*it).type.numFrames, game, (*it).type.npc);
        PlayerProperty p;
        getBotProperty(*it, p);
        bot->setPhysics(p);
        bot->setFPS((*it).type.fps);

        game->addBot(bot);
    }
}


void setupGame(string filename, MainWindow* w, Game* game)
{
    std::size_t found = filename.find_last_of("/\\");
    string path = filename.substr(0, found);
    XML xml = XML(filename);


    //create Level
   setupLevel(w,game,path+"/"+xml.getTileset());

    //create Background layer
    setupBackground(xml.getBackground(),path+"/"+xml.getBackground().filename,w,game);




    //add statusbar
    setupStatusbar(w,game,xml.getStatusbar(),path+"/"+xml.getStatusbar().filename);

    //add player
    setupPlayer(xml.getPlayer(),w,game,path);

   //setup bots
    setupBots(xml.getLevelBots(),w,game,path);




}

int main(int argc, char** argv)
{

	if(argc != 2)
	{
		std::cout << "Please specify a level to render" << std::endl;
		return -1;
	}

	MainWindow window("Ikaruga", 625, 576);
	Game game(&window);
	setupGame(argv[1], &window, &game);

	window.setGame(&game);
	game.start();
	window.run();

	// Free textures
	TextureFactory::instance(window.getRenderer()).deleteAll();

}
