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
    ptree tileset;
    ptree background;
    ptree player;

    /* Adding Level Information */
    level.put("id", m_id);
    level.put("name", m_levelname);

    /* Adding Tileset */
    tileset.put("<xmlattr>.filename", m_tileset);

    level.add_child("tileset", tileset);

    /* Adding Background */
    background.put("<xmlattr>.filename", m_background.filename);
    background.put("scrollspeed", m_background.scrollspeed);

    level.add_child("background", background);

    /* Adding Player */
    player.put("<xmlattr>.filename", m_player.filename);
    player.put("frameWidth", m_player.frameWidth);
    player.put("frameHeight", m_player.frameHeight);
    player.put("positionY", m_player.positionY);
    player.put("stdWeapon", m_player.stdWeapon);

    level.add_child("player", player);

    /* Adding Bots */
    for(int i=0;i<(int) m_bots.size();i++) {
        ptree bot, npc, move, weapon;
        bot.put("<xmlattr>.filename", m_bots[i].filename);
        bot.put("frameWidth", m_bots[i].frameWidth);
        bot.put("frameHeight", m_bots[i].frameHeight);
        bot.put("tileID", m_bots[i].tileID);
        bot.put("positionX", m_bots[i].positionX);
        bot.put("positionY", m_bots[i].positionY);


        npc.put("<xmlattr>.type", m_bots[i].npc.type);
        move.put("<xmlattr>.function", m_bots[i].npc.move_function);
        npc.add_child("move", move);
        npc.put("move", m_bots[i].npc.move_value);
        npc.put("fireRate", m_bots[i].npc.fireRate);
        npc.put("speed", m_bots[i].npc.speed);
        weapon.put("<xmlattr>.type", m_bots[i].npc.weapon_type);
        npc.add_child("weapon", weapon);
        npc.put("weapon", m_bots[i].npc.weapon_level);

        bot.add_child("npc", npc);
        bot.put("color", m_bots[i].color);
        level.add_child("bot", bot);
    }

    /* Adding Items */
    for(int i=0;i<(int) m_items.size();i++) {
        ptree item;
        item.put("<xmlattr>.filename", m_items[i].filename);
        item.put("frameWidth", m_items[i].frameWidth);
        item.put("frameHeight", m_items[i].frameHeight);
        item.put("positionX", m_items[i].positionX);
        item.put("positionY", m_items[i].positionY);
        item.put("type", m_items[i].type);

        level.add_child("item", item);
    }

    /* Setting up XML-Tree with root-Node */
    root.add_child("level", level);
    write_xml("/home/skalbers/Studium/GITHUB_Praktikum/res/levels/testXml.xml", root, std::locale(), xml_writer_make_settings<ptree::key_type>('    ', 4u));
}


