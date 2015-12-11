#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include "MainWindow.hpp"
#include "Game.hpp"
#include "TextureFactory.hpp"

#include <iostream>

using namespace jumper;
using std::string;
using std::cout;
using std::endl;

void setupGame(string filename, Game* game)
{
	 std::size_t found = filename.find_last_of("/\\");
	 string path = filename.substr(0,found);

	 using boost::property_tree::ptree;
	 ptree pt;
	 read_xml(filename, pt);

	 BOOST_FOREACH(const ptree::value_type&  v, pt.get_child("level") )
	 {
		 if( v.first == "bot" ) {

			 string filename = v.second.get("<xmlattr>.filename", "");
			 int pos_x = v.second.get<int>("positionX", 0);
			 int pos_y = v.second.get<int>("positionY", 0);
			 int numFrames = v.second.get<int>("numFrames", 0);
			 cout << filename << " " << pos_x << " " << pos_y << " " << endl;
		 }
		 if( v.first == "tileset")
		 {
			 string filename = v.second.get("<xmlattr>.filename", "");
			 cout << filename << endl;
		 }
	 }

}

int main(int argc, char** argv)
{
	if(argc != 4)
	{
		std::cout << "Please specify a level to render" << std::endl;
		return -1;
	}

	MainWindow window("Jumper", 800, 600);
	Game game(&window);
	setupGame(argv[1], &game);

	window.setGame(&game);
	window.run();

	// Free textures
	TextureFactory::instance(window.getRenderer()).deleteAll();
}
