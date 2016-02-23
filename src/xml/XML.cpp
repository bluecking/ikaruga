#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <iostream>
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

    // TODO catch errors

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

            Bot bot;
            bot.filename = v.second.get<string>("<xmlattr>.filename");
            bot.frameWidth = v.second.get<int>("frameWidth");
            bot.frameHeight = v.second.get<int>("frameHeight");
            bot.tileID = v.second.get<int>("tileID");
            bot.positionX = v.second.get<int>("positionX");
            bot.positionY = v.second.get<int>("positionY");
            bot.color = v.second.get<string>("color");

            /* Get data from child node NPC */
            NPC npc;
            npc.type = v.second.get_child("npc").get<string>("<xmlattr>.type");
            npc.move_function = v.second.get_child("npc").get_child("move").get<string>("<xmlattr>.function");
            npc.move_value = v.second.get_child("npc").get<signed int>("move");
            npc.fireRate = v.second.get_child("npc").get<unsigned int>("fireRate");
            npc.speed = v.second.get_child("npc").get<signed int>("speed");
            npc.weapon_type = v.second.get_child("npc").get_child("weapon").get<string>("<xmlattr>.type");
            npc.weapon_level = v.second.get_child("npc").get<unsigned int>("weapon");
            bot.npc = npc;
            m_bots.push_back(bot);

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
}

