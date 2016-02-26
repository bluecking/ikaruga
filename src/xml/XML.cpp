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
                m_player.numFrames = v.second.get<int>("numFrames");
                m_player.frameWidth = v.second.get<int>("frameWidth");
                m_player.frameHeight = v.second.get<int>("frameHeight");
                m_player.positionX = v.second.get<int>("positionX");
                m_player.positionY = v.second.get<int>("positionY");
                m_player.stdWeapon = v.second.get<string>("stdWeapon");
                m_player.colorOffsetX = v.second.get<int>("colorOffsetX");
                m_player.colorOffsetY = v.second.get<int>("colorOffsetY");
                m_player.moveForceX = v.second.get<float>("moveForceX");
                m_player.moveForceY = v.second.get<float>("moveForceY");
                m_player.maxVel = v.second.get<float>("maxVel");
                m_player.fps = v.second.get<int>("fps");
                m_requiredAttributes["player"]++;
            }
            else if (v.first == "bot")
            {
                LevelBot lBot;
                std::string type_tmp = v.second.get<string>("<xmlattr>.type");
                for (auto it = begin(m_bots); it != end(m_bots); it++)
                {
                    if(type_tmp.compare(it->type)==0)
                    {
                        lBot.type = *it;
                    }
                    else
                    {
                        throw std::domain_error("Found unknown xml tag " + type_tmp + " on level.");
                    }
                }
                lBot.positionX = v.second.get<int>("positionX");
                lBot.positionY = v.second.get<int>("positionY");
                lBot.color = v.second.get<string>("color");
                lBot.powerUpProb = v.second.get_child("powerUp").get<int>("<xmlattr>.probability");
                lBot.powerUpName = v.second.get<string>("powerUp");

                m_level_bots.push_back(lBot);
            }
            else if (v.first == "item")
            {
                LevelItem lItem;
                lItem.type = v.second.get<string>("<xmlattr>.type");
                lItem.positionX = v.second.get<int>("positionX");
                lItem.positionY = v.second.get<int>("positionY");
                lItem.value = v.second.get<int>("value");

                m_level_items.push_back(lItem);
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

void XML::loadBots(std::string filename){
    ptree pt;
    try
    {
        read_xml(filename, pt);
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e) {
        std::cerr << boost::diagnostic_information(e);
        throw std::invalid_argument("Invalid path or filename.");
    }

    try
    {
        BOOST_FOREACH(const ptree::value_type& v, pt.get_child("bots"))
        {
            if (v.first == "bot")
            {
                Bot bot;
                bot.type = v.second.get<string>("<xmlattr>.tpye");
                bot.filename = v.second.get<string>("filename");
                bot.numFrames = v.second.get<int>("numFrames");
                bot.frameWidth = v.second.get<int>("frameWidth");
                bot.frameHeight = v.second.get<int>("frameHeight");
                bot.tileID = v.second.get<int>("tileID");
                bot.colorOffsetX = v.second.get<int>("colorOffsetX");
                bot.colorOffsetY = v.second.get<int>("colorOffsetY");
                bot.fps = v.second.get<int>("fps");

                /* Get data from child node NPC */
                NPC npc;
                npc.type = v.second.get_child("npc").get<string>("<xmlattr>.type");
                npc.move_function = v.second.get_child("npc").get_child("move").get<string>("<xmlattr>.function");
                npc.move_value = v.second.get_child("npc").get <signed int> ("move");
                npc.speed = v.second.get_child("npc").get <signed int> ("speed");
                npc.stdWeapon = v.second.get_child("npc").get <string> ("stdWeapon");
                bot.npc = npc;
                m_bots.push_back(bot);
            }
            else
            {
                throw std::domain_error("Found unknown xml tag " + v.first + " on first child layer below bots.");
            }
        }
    }
    catch (boost::exception const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::domain_error("XML parsing failed. Did you use an invalid tag or attribute?");
    }
}

void XML::loadItems(std::string filename){
    ptree pt;
    try
    {
        read_xml(filename, pt);
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e) {
        std::cerr << boost::diagnostic_information(e);
        throw std::invalid_argument("Invalid path or filename.");
    }

    try
    {
        BOOST_FOREACH(const ptree::value_type& v, pt.get_child("items"))
        {
            if (v.first == "item")
            {
                Item i;
                i.type = v.second.get<string>("<xmlattr>.type");
                i.filename = v.second.get<string>("filename");
                i.frameWidth = v.second.get<int>("frameWidth");
                i.frameHeight = v.second.get<int>("frameHeight");
                m_items.push_back(i);
            }
            else
            {
                throw std::domain_error("Found unknown xml tag " + v.first + " on first child layer below items.");
            }
        }
    }
    catch (boost::exception const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::domain_error("XML parsing failed. Did you use an invalid tag or attribute?");
    }
}

void XML::loadWeapons(std::string filename){
    ptree pt;
    try
    {
        read_xml(filename, pt);
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e) {
        std::cerr << boost::diagnostic_information(e);
        throw std::invalid_argument("Invalid path or filename.");
    }

    try
    {
        BOOST_FOREACH(const ptree::value_type& v, pt.get_child("weapons"))
        {
            if (v.first == "weapon")
            {
                Weapon w;
                w.type = v.second.get<string>("<xmlattr>.type");
                w.filename = v.second.get<string>("filename");
                w.colorOffsetX = v.second.get<int>("colorOffsetX");
                w.colorOffsetY = v.second.get<int>("colorOffsetY");
                m_weapons.push_back(w);
            }
            else
            {
                throw std::domain_error("Found unknown xml tag " + v.first + " on first child layer below weapons.");
            }
        }
    }
    catch (boost::exception const& e)
    {
        std::cerr << boost::diagnostic_information(e);
        throw std::domain_error("XML parsing failed. Did you use an invalid tag or attribute?");
    }
}

void XML::save()
{
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
    player.put("numFrames", m_player.frameWidth);
    player.put("frameWidth", m_player.frameWidth);
    player.put("frameHeight", m_player.frameHeight);
    player.put("positionX", m_player.positionX);
    player.put("positionY", m_player.positionY);
    player.put("stdWeapon", m_player.stdWeapon);
    player.put("colorOffsetX", m_player.colorOffsetX);
    player.put("colorOffsetY", m_player.colorOffsetY);
    player.put("moveForceX", m_player.moveForceX);
    player.put("moveForceY", m_player.moveForceY);
    player.put("maxVel", m_player.maxVel);
    player.put("fps", m_player.fps);

    level.add_child("player", player);

    /* Adding Level_Bots */
    for(int i=0;i<(int) m_level_bots.size();i++) {
        ptree level_bot, powerUp;
        level_bot.put("<xmlattr>.type", m_level_bots[i].type.type);
        level_bot.put("positionX", m_level_bots[i].positionX);
        level_bot.put("positionY", m_level_bots[i].positionY);
        level_bot.put("color", m_level_bots[i].color);

        powerUp.put("<xmlattr>.probability", m_level_bots[i].powerUpProb);
        level_bot.add_child("powerUp", powerUp);
        level_bot.put("powerUp", m_level_bots[i].powerUpName);

        level.add_child("bot", level_bot);
    }

    /* Adding Level_Items */
    for(int i=0;i<(int) m_level_items.size();i++) {
        ptree level_item;
        level_item.put("<xmlattr>.type", m_level_items[i].type);
        level_item.put("positionX", m_level_items[i].positionX);
        level_item.put("positionY", m_level_items[i].positionY);
        level_item.put("value", m_level_items[i].value);

        level.add_child("item", level_item);
    }

    /* Setting up XML-Tree with root-Node */
    root.add_child("level", level);

    try
    {
        //Automatic indents of the xml file does not work on the same way with different versions because of a bug in
        //the boost library.
        //The following line works in boost 1.60, 1.58:
        //write_xml(getFilename(), root, std::locale(), xml_writer_make_settings<ptree::key_type>(' ', 4u));
        //The following line works in boost 1.54:
        //boost::property_tree::xml_writer_settings<char> settings (' ', 4u); write_xml(getFilename(), root, std::locale(), settings);
        //Without pretty format (all XML tags in one line) it works in all boost versions
        //write_xml(getFilename(), root, std::locale(), xml_writer_make_settings<ptree::key_type>(' ', 4u));
        write_xml(getFilename(), root, std::locale());
    }
    catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::property_tree::xml_parser::xml_parser_error> > const& e) {
        std::cerr << boost::diagnostic_information(e);
        throw std::ios_base::failure("Cannot write file. Is it readonly?");
    }
}

/* Level Bots/Items - Getter/Setter */
void XML::setLevelItem(unsigned int position, XML::LevelItem lItem)
{
    if(position >= levelItemSize()) {throw std::range_error("Index out of range.");}
    m_level_items[position] = lItem;
}

void XML::setLevelBot(unsigned int position, XML::LevelBot lBot)
{
    if(position >= levelBotSize()) {throw std::range_error("Index out of range.");}
    m_level_bots[position] = lBot;
}

XML::LevelBot XML::getLevelBot(unsigned int number)
{
    if(number >= levelBotSize()) {throw std::range_error("Index out of range.");}
    return m_level_bots[number];
}

XML::LevelItem XML::getLevelItem(unsigned int number)
{
    if(number >= levelItemSize()) {throw std::range_error("Index out of range.");}
    return m_level_items[number];
}

void XML::removeLevelItem(unsigned int position)
{
    if(position >= levelItemSize()) {throw std::range_error("Index out of range.");}
    m_level_items.erase(m_level_items.begin() + position);
}

void XML::removeLevelBot(unsigned int position)
{
    if(position >= levelBotSize()) {throw std::range_error("Index out of range.");}
    m_level_bots.erase(m_level_bots.begin() + position);
}

/* Definition Getter */
XML::Bot XML::getBot(unsigned int number)
{
    if(number >= botSize()) {throw std::range_error("Index out of range.");}
    return m_bots[number];
}

XML::Item XML::getItem(unsigned int number)
{
    if(number >= itemSize()) {throw std::range_error("Index out of range.");}
    return m_items[number];
}

XML::Weapon XML::getWeapon(unsigned int number)
{
    if(number >= weaponSize()) {throw std::range_error("Index out of range.");}
    return m_weapons[number];
}