#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include "MainWindow.hpp"
#include "Game.hpp"
#include "TextureFactory.hpp"
#include "TexturedLayer.hpp"
#include "Item.hpp"

#include <iostream>

using namespace jumper;
using std::string;
using std::cout;
using std::endl;

void getPlayerProperty(const boost::property_tree::ptree::value_type& v, PlayerProperty& p)
{
	int pos_x = v.second.get<int>("positionX", 0);
	int pos_y = v.second.get<int>("positionY", 0);
	float jumpForceX = v.second.get<float>("jumpForceX", 0.0);
	float jumpForceY = v.second.get<float>("jumpForceY", 0.0);
	float moveForceX = v.second.get<float>("moveForceX", 0.0);
	float moveForceY = v.second.get<float>("moveForceY", 0.0);
	float maxVelRun = v.second.get<float>("maxVelRun", 0.0);
	float maxVelFall = v.second.get<float>("maxVelFall", 0.0);
	float maxJumpHeight = v.second.get<float>("maxJumpHeight", 0.0);

	p.setPosition(Vector2f(pos_x, pos_y));
	p.setJumpForce(Vector2f(jumpForceX, jumpForceY));
	p.setMoveForce(Vector2f(moveForceX, moveForceY));
	p.setMaxFallVelocity(maxVelFall);
	p.setMaxRunVelocity(maxVelRun);
	p.setMaxJumpHeight(maxJumpHeight);
}

void setupGame(string filename, MainWindow* w, Game* game)
{
	 std::size_t found = filename.find_last_of("/\\");
	 string path = filename.substr(0,found);

	 using boost::property_tree::ptree;
	 ptree pt;
	 read_xml(filename, pt);

	 BOOST_FOREACH(const ptree::value_type&  v, pt.get_child("level") )
	 {
		 if( v.first == "bot" || v.first == "player" || v.first == "item")
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
				 Bot* bot = new Bot(w->getRenderer(), texture, frameWidth, frameHeight, numFrames);
				 game->addActor(bot);
				 actor = bot;
			 }
			 else if(v.first == "player")
			 {
				 Player* player = new Player(w->getRenderer(), texture, frameWidth, frameHeight, numFrames);
				 game->setPlayer(player);
				 player->setFocus(true);
				 actor = player;
			 }
			 else if(v.first == "item")
			 {
				 Item* item = new Item(w->getRenderer(), texture, frameWidth, frameHeight, numFrames);
				 game->addActor(item);
				 actor = item;
			 }

			 // Setup actor properties
			 if(actor)
			 {
				 PlayerProperty p;
				 getPlayerProperty(v, p);
				 actor->setPhysics(p);
				 actor->setFPS(fps);
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
			 TexturedLayer* layer = new TexturedLayer(w->getRenderer(), texture);
			 layer->setScrollSpeed(s);
			 game->setLayer(layer);
		 }

	 }

}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cout << "Please specify a level to render" << std::endl;
		return -1;
	}

	MainWindow window("Jumper", 800, 600);
	Game game(&window);
	setupGame(argv[1], &window, &game);

	window.setGame(&game);
	game.start();
	window.run();

	// Free textures
	TextureFactory::instance(window.getRenderer()).deleteAll();
}
