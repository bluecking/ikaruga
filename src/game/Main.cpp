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


int main(int argc, char** argv)
{

 if(argc != 2)
    {
        std::cout << "Invalid amount of parameters." << std::endl;
        return -1;
    }

    MainWindow window("Ikaruga", 625, 576);
    Game game(&window);
    MainMenu menu(&window, &game, boost::filesystem::path(argv[1]));

    window.setMenu(&menu);

    window.setActualScreen(MainWindow::RENDER_MAINMENU);
    window.run();

    // Free textures
    TextureFactory::instance(window.getRenderer()).deleteAll();
}
