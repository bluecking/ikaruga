/**
* @file XML.h
* @brief Imports a xml file with game specifications
*
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
* @date 23 Feb 2016
*/

#ifndef XML_HPP
#define XML_HPP

#include <vector>
#include <map>
#include <boost/exception/all.hpp>

class XML {
public:
    //Public structs for xml nodes
    struct NPC{
        std::string type;
        std::string move_function;
        signed int move_value;
//        unsigned int fireRate;
        signed int speed;
//        std::string weapon_type;
//        unsigned int weapon_level;
        std::string stdWeapon;
    };

    struct Player{
        std::string filename;
        int numFrames;
        int frameWidth;
        int frameHeight;
        int positionX;
        int positionY;
        std::string stdWeapon;
        int colorOffsetX;
        int colorOffsetY;
        float moveForceX;
        float moveForceY;
        float maxVel;
        int fps;
    };

    struct Bot{
        std::string type;
        std::string filename;
        int numFrames;
        int frameWidth;
        int frameHeight;
        int tileID;
        int colorOffsetX;
        int colorOffsetY;
        int fps;
        NPC npc;
    };

    struct LevelBot{
        std::string type;
        int positionX;
        int positionY;
        std::string color;
        int powerUpProb;
        std::string powerUpName;
    };

    struct Item{
        std::string type;
        std::string filename;
        int frameWidth;
        int frameHeight;
    };

    struct LevelItem{
        std::string type;
        int positionX;
        int positionY;
        int value;
    };

    struct Background{
        std::string filename;
        int scrollspeed;
    };

    struct Weapon{
        std::string type;
        std::string filename;
        int colorOffsetX;
        int colorOffsetY;
    };

    /**
     * This constructor loads the given xml file. Exceptions as documented for the load() method can occur.
     * @param xmlFilename Name of xmlFile with level information.
     */
    XML(std::string xmlFilename);

    /**
     * This constructor generates a minimal level specification with default values.
     */
    XML();

    void loadBots(std::string filename);
    void loadItems(std::string filename);
    void loadWeapon(std::string filename);

    /**
     * Stores game information into XML file. By default it overwrites the original file. If desired you can specify
     * another location by the setFilename method.
     * @throw std::ios_base::failure If file could not be saved.
     */
    void save();

    /**
     * Set XML filename.
     * @param filename XML file for game specification.
     */
    void setFilename(std::string filename) {m_filename = filename;}

    /**
     * Get current name of XML file for level specification.
     * @return XML filename
     */
    std::string getFilename() { return m_filename;}

    /**
     * Set level id.
     * @param id Unique level id.
     */
    void setId(int id) {m_id = id;}

    /**
     * Set level name.
     * @param levelname Name of level.
     */
    void setLevelname(const std::string& levelname)
    {
        m_levelname = levelname;
    }

    /**
     * Set tileset.
     * @param tileset The tileset.
     */
    void setTileset(const std::string& tileset)
    {
        m_tileset = tileset;
    }

    /**
     * Set background.
     * @param background The background.
     */
    void setBackground(const Background& background)
    {
        m_background = background;
    }

    /**
     * Set Player.
     * @param The player.
     */
    void setPlayer(const Player& player)
    {
        m_player = player;
    }

    /**
     * Get level id.
     * @return level id.
     */
    int getId() { return m_id;}

    /**
     * Set all bots at a time.
     * @param bots vector of bots.
     */
    void setBots(const std::vector<Bot>& bots)
    {
        m_bots = bots;
    }

    /**
     * Set single bot.
     * @param Number of the bot.
     * @param bot The bot.
     * @throw range_error If no bot is available with the given number.
     */
    void setBot(unsigned int position, Bot bot);

    /**
     * Set all bots at a time.
     * @param items Vector of items
     */
    void setItems(const std::vector<Item>& items)
    {
        m_items = items;
    }

    /**
     * Set single item.
     * @param position Number of the bot.
     * @param item The item.
     * @throw range_error If no item is available with the given number.
     */
    void setItem(unsigned int position, Item item);

    /**
     * Get the current Levelname
     * @return m_levelname
     */
    std::string getLevelname() { return m_levelname;}

    /**
     * Get the current tileset
     * @return m_tileset
     */
    std::string getTileset() { return m_tileset;}

    /**
     * Get the current Background
     * @return m_background
     */
    Background getBackground() { return m_background;}

    /**
     * Get the Player
     * @return m_player
     */
    Player getPlayer() { return m_player;}

    /**
     * Get all Bots
     * @return Vector wit all Bots
     */
    std::vector<Bot> getBots() { return m_bots;}

    /**
     * Get the Bot at given number
     * @param number Position of Bot
     * @return Bot at position number
     * @throw range_error If no bot is available with the given number.
     */
    Bot getBot(unsigned int number);

    /**
     * Get all Items
     * @return Vector with all Items
     */
    std::vector<Item> getItems() { return m_items;}

    /**
     * Get all Weapons
     * @return Vector with all Weapons
     */
    std::vector<Weapon> getWeapons() { return m_weapons;}

    /**
     * Get the Item at given number
     * @param number Position of Item
     * @return Item at position number
     * @throw range_error If no item is available with the given number.
     */
    Item getItem(unsigned int number);

    /**
     * Add an additional item.
     * @param item The new item.
     */
    void addItem(Item item) {m_items.push_back(item);}

    /**
     * Add additional bot.
     * @param bot The new bot.
     */
    void addBot(Bot bot) {m_bots.push_back(bot);}

    /**
     * Remove an item.
     * @param position The number of the item.
     * @throw range_error If no item is available with the given number.
     */
    void removeItem(unsigned int position);

    /**
     * Remove a bot.
     * @param position Number of the bot.
     * @throw range_error If no bot is available with the given number.
     */
    void removeBot(unsigned int position);

    /**
     * Returns the total number of bots.
     * @return Total number of bots.
     */
    unsigned int botSize() {return m_bots.size();}

    /**
     * Returns the total number of items.
     * @return Total number of items.
     */
    unsigned int itemSize() {return m_items.size();}

    /**
     * Returns the total number of weapons.
     * @return Total number of weapons.
     */
    unsigned int weaponSize() {return m_weapons.size();}

private:
    /* XML Filename */
    std::string m_filename;

    /* XML Data Variables */
    int m_id;
    std::string m_levelname;
    std::string m_tileset;
    Background m_background;
    Player m_player;
    std::vector<XML::Bot> m_bots;
    std::vector<XML::LevelBot> m_level_bots;
    std::vector<XML::Item> m_items;
    std::vector<XML::LevelItem> m_level_items;
    std::vector<XML::Weapons> m_weapons;
    std::map<std::string, int> m_requiredAttributes;

    /**
     * Load XML game information into several structures.
     * @throw domain_error If unknown tag found or the xml file does not contain all required attributes.
     * @throw invalid_argument If xml file could not be accessed.
     */
    void load();

    /**
     * Initialize some variables with default values. Required by the constructors.
     */
    void init();
};

#endif //XML_HPP
