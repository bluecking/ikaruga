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
        unsigned int fireRate;
        signed int speed;
        std::string weapon_type;
        unsigned int weapon_level;
    };

    struct Player{
        std::string filename;
        int frameWidth;
        int frameHeight;
        int positionY;
        std::string stdWeapon;
    };

    struct Bot{
        std::string filename;
        int frameWidth;
        int frameHeight;
        int tileID;
        int positionX;
        int positionY;
        NPC npc;
        std::string color;
    };

    struct Item{
        std::string filename;
        int frameWidth;
        int frameHeight;
        int positionX;
        int positionY;
        std::string type;
    };

    struct Background{
        std::string filename;
        int scrollspeed;
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

    /**
     * Stores game information into XML file. By default it overwrites the original file. If desired you can specify
     * another location by the setFilename method.
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

    //TODO add doxygen
    void setId(int id)
    {
        m_id = id;
    }

    void setLevelname(const std::string& levelname)
    {
        m_levelname = levelname;
    }

    void setTileset(const std::string& tileset)
    {
        m_tileset = tileset;
    }

    void setBackground(const Background& background)
    {
        m_background = background;
    }

    void setPlayer(const Player& player)
    {
        m_player = player;
    }

    int getId() { return m_id;}

    std::string getLevelname() { return m_levelname;}

    std::string getTileset() { return m_tileset;}

    Background getBackground() { return m_background;}

    Player getPlayer() { return m_player;}

    std::vector<Bot> getBots() { return m_bots;} //TODO Do not use in productive environment it maybe will be changed.

    std::vector<Item> getItems() { return m_items;} // TODO Do not use in productive environment it maybe will be changed.


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
    std::vector<XML::Item> m_items;
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
