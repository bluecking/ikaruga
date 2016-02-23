#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <vector>
#include "XML.hpp"

using std::string;
using std::cout;
using std::endl;
using boost::property_tree::ptree;

void XML::load() {
    std::size_t found = XML::getFilename().find_last_of("/\\");
    string path = XML::getFilename().substr(0, found);

    ptree pt;
    read_xml(XML::getFilename(), pt);

/*
    BOOST_FOREACH( ptree::value_type const& v, pt.get_child("sked") ) {
                    if( v.first == "flight" ) {
                        Flight f;
                        f.carrier = v.second.get<std::string>("carrier");
                        f.number = v.second.get<unsigned>("number");
                        f.date = v.second.get<Date>("date");
                        f.cancelled = v.second.get("<xmlattr>.cancelled", false);
                        ans.push_back(f);
                    }
                }


*/

    //-------------------------------

    // TODO catch errors
//    m_id = pt.get<int>("level.id");
//    m_levelname = pt.get<std::string>("level.name");

	BOOST_FOREACH(const ptree::value_type&  v, pt.get_child("level") )
	{
        if(v.first == "id") {
            m_id = v.second.get<int>("");
        }
        else if(v.first == "name") {
            m_levelname = v.second.get<string>("");
        }
        else if(v.first == "tileset") {
            m_tileset = v.second.get<string>("<xmlattr>.filename");
        }
        else if(v.first == "background") {
            m_background.filename = v.second.get<string>("<xmlattr>.filename");
            m_background.scrollspeed = v.second.get<int>("scrollspeed");
        }
        else if(v.first == "player") {
            m_player.filename = v.second.get<string>("<xmlattr>.filename");
            m_player.frameWidth = v.second.get<int>("frameWidth");
            m_player.frameHeight = v.second.get<int>("frameHeight");
            m_player.positionY = v.second.get<int>("positionY");
            m_player.stdWeapon = v.second.get<string>("stdWeapon");
        }
        else if(v.first == "bot") {
            Bot b;
            b.filename = v.second.get<string>("<xmlattr>.filename");
            b.frameWidth = v.second.get<int>("frameWidth");
            b.frameHeight = v.second.get<int>("frameHeight");
            b.tileID = v.second.get<int>("tileID");
            b.positionX = v.second.get<int>("positionX");
            b.positionY = v.second.get<int>("positionY");
            b.color = v.second.get<string>("color");
            m_bots.push_back(b);
        }
        else if(v.first == "item") {
            Item i;
            i.filename = v.second.get<string>("<xmlattr>.filename");
            i.frameWidth = v.second.get<int>("frameWidth");
            i.frameHeight = v.second.get<int>("frameHeight");
            i.positionX = v.second.get<int>("positionX");
            i.positionY = v.second.get<int>("positionY");
            i.type = v.second.get<string>("type");
            m_items.push_back(i);
        }
    }
/*




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
*/
}

//}

