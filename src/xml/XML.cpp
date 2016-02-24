#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include "XML.hpp"

using std::string;
using std::cout;
using std::endl;
using boost::property_tree::ptree;
using boost::property_tree::xml_writer_make_settings;

XML::XML(std::string xmlFilename)
{
    setFilename(xmlFilename);
    init();
    load();
}

XML::XML()
{
    init();
    setId(0);
    setLevelname("Levelname");
    setTileset("tileset.lvl");
    Background b;
    b.filename = "background.png";
    b.scrollspeed = 0;
    setBackground(b);
    Player p;
    p.filename = "player.png";
    p.frameWidth = 1;
    p.frameHeight = 1;
    p.positionY = 0;
    p.stdWeapon = "pitchfork";
    setPlayer(p);
}

void XML::init()
{
    //Initialize required attributes for a minimal xml file.
    m_requiredAttributes.insert(std::pair<string, int>("id", 0));
    m_requiredAttributes.insert(std::pair<string, int>("name", 0));
    m_requiredAttributes.insert(std::pair<string, int>("tileset", 0));
    m_requiredAttributes.insert(std::pair<string, int>("background", 0));
    m_requiredAttributes.insert(std::pair<string, int>("player", 0));
}

void XML::load()
{
    std::size_t found = XML::getFilename().find_last_of("/\\");
    string path = XML::getFilename().substr(0, found);

    ptree pt;
    try
    {
        read_xml(XML::getFilename(), pt);
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e) {
        std::cerr << boost::diagnostic_information(e);
        throw std::invalid_argument("Invalid path or filename.");
    }

    try
    {
        BOOST_FOREACH(const ptree::value_type& v, pt.get_child("level"))
                    {

                        if (v.first == "id")
                        {
                            m_id = v.second.get<int>("");
                            m_requiredAttributes["id"]++;
                        }
                        else if (v.first == "name")
                        {
                            m_levelname = v.second.get<string>("");
                            m_requiredAttributes["name"]++;
                        }
                        else if (v.first == "tileset")
                        {
                            m_tileset = v.second.get<string>("<xmlattr>.filename");
                            m_requiredAttributes["tileset"]++;
                        }
                        else if (v.first == "background")
                        {
                            m_background.filename = v.second.get<string>("<xmlattr>.filename");
                            m_background.scrollspeed = v.second.get<int>("scrollspeed");
                            m_requiredAttributes["background"]++;
                        }
                        else if (v.first == "player")
                        {
                            m_player.filename = v.second.get<string>("<xmlattr>.filename");
                            m_player.frameWidth = v.second.get<int>("frameWidth");
                            m_player.frameHeight = v.second.get<int>("frameHeight");
                            m_player.positionY = v.second.get<int>("positionY");
                            m_player.stdWeapon = v.second.get<string>("stdWeapon");
                            m_requiredAttributes["player"]++;
                        }
                        else if (v.first == "bot")
                        {
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
                            npc.move_function = v.second.get_child("npc").get_child("move").get<string>(
                                    "<xmlattr>.function");
                            npc.move_value = v.second.get_child("npc").get < signed int > ("move");
                            npc.fireRate = v.second.get_child("npc").get < unsigned int > ("fireRate");
                            npc.speed = v.second.get_child("npc").get < signed int > ("speed");
                            npc.weapon_type = v.second.get_child("npc").get_child("weapon").get<string>("<xmlattr>.type");
                            npc.weapon_level = v.second.get_child("npc").get < unsigned int > ("weapon");
                            bot.npc = npc;
                            m_bots.push_back(bot);
                        }
                        else if (v.first == "item")
                        {
                            Item i;
                            i.filename = v.second.get<string>("<xmlattr>.filename");
                            i.frameWidth = v.second.get<int>("frameWidth");
                            i.frameHeight = v.second.get<int>("frameHeight");
                            i.positionX = v.second.get<int>("positionX");
                            i.positionY = v.second.get<int>("positionY");
                            i.type = v.second.get<string>("type");
                            m_items.push_back(i);
                        }
                        else
                        {
                            throw std::domain_error("Found unknown xml tag " + v.first + " on first child layer below level.");
                        }
                    }
    }
    catch (boost::exception const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::domain_error("XML parsing failed. Did you use an invalid tag or attribute?");
    }

    //Check if it was possible to read the required number of the following tags.
    if (m_requiredAttributes["id"] != 1) //One id tag is required
    { throw std::domain_error("Required attribute id not available."); }
    if (m_requiredAttributes["name"] != 1)
    { throw std::domain_error("Required attribute name not available."); }
    if (m_requiredAttributes["tileset"] != 1)
    { throw std::domain_error("Required attribute tileset not available."); }
    if (m_requiredAttributes["background"] != 1)
    { throw std::domain_error("Required attribute background not available."); }
    if (m_requiredAttributes["player"] != 1)
    { throw std::domain_error("Required attribute player not available."); }
}

void XML::save()
{
    //TODO implement and exception handling
    ptree root;
    ptree level;
    ptree player;
    ptree player_infos;

//    player.add_child("frameWidth", m_player.frameWidth);
//    player.add_child("frameHeight", m_player.frameHeight);
//    player.add_child("positionY", m_player.positionY);
//    player.add_child("stdWeapon", m_player.stdWeapon);
    player_infos.put("frameWidth", m_player.frameWidth);
    player_infos.put("frameHeight", m_player.frameHeight);
    player_infos.put("positionY", m_player.positionY);
    player_infos.put("stdWeapon", m_player.stdWeapon);

    player.put("<xmlattr>.filename", m_player.filename);
    //player.add_child("", player_infos);

    //boost::property_tree::xml_writer_settings< char > settings('\t', 1);
    write_xml("/home/patrick/Git-Repositories/uni_hausaufgaben/praktikum1/res/levels/testXml.xml", player_infos, std::locale(), xml_writer_make_settings<ptree::key_type>(' ', 1u));
//    player.add_child(player_infos)
}


