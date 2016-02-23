#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include <iostream>

using std::string;
using std::cout;
using std::endl;


struct Player{
	int frameWidth;
	int frameHeight;
	int posY;
	string stdWeapon;
};

struct Bot{
	int frameWidth;
	int frameHeight;
	int posX;
	int posY;
	string typ;
	string color;
};

struct Item{
	int frameWidth;
	int frameHeight;
	int posX;
	int posY;
	string typ;
};

void parseLevel(string filename)
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


			 if(v.first == "bot")
			 {

			 }
			 else if(v.first == "player")
			 {

			 }
			 else if(v.first == "item")
			 {

			 }
		 }
		 if( v.first == "tileset")
		 {
			 string filename = v.second.get("<xmlattr>.filename", "");
		 }
		 if( v.first == "name")
		 {
			 string filename = v.second.get("<xmlattr>.filename", "");
		 }
		 if( v.first == "id")
		 {
			 string filename = v.second.get("<xmlattr>.filename", "");
		 }


	 }

}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cout << "Please specify a level to render" << std::endl;
		//return -1;
	}

	parseLevel(argv[1]);
}
