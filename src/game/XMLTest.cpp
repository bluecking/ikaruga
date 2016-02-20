#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	using boost::property_tree::ptree;
	ptree pt;
	read_xml(argv[1], pt);

	BOOST_FOREACH(const ptree::value_type&  v, pt.get_child("level") ) {
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


	return 0;
}
