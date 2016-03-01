#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include "MainWindow.hpp"
#include "Game.hpp"
#include "TextureFactory.hpp"
#include "TexturedLayer.hpp"
#include "Item.hpp"
#include "PuzzleBox.hpp"
#include "../xml/XML.hpp"
#include <iostream>
#include "MainMenu.hpp"
#include <boost/filesystem/path.hpp>

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

int main(int argc, char** argv)
{

 if(argc != 2)
    {
        std::cout << "Invalid amount of parameters." << std::endl;
        return -1;
    }

    MainWindow window("Ikaruga", 625, 576);
    Game game(&window);
    MainMenu menu(&window, boost::filesystem::path(argv[1]));

    window.setActualScreen(MainWindow::RENDER_ITEMSHOP);
    window.run();

    // Free textures
    TextureFactory::instance(window.getRenderer()).deleteAll();
}
