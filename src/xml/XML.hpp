/**
* @file XML.h
* @brief Imports a xml file with game specifications
*
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
* @date 23 Feb 2016
*/
#ifndef JUMPER_XML_HPP
#define JUMPER_XML_HPP

class XML {
public:
    struct Player{
        std::string filename;
        int frameWidth;
        int frameHeight;
        int positionY;
        std::string stdWeapon;
    };

    struct Bot{
        int frameWidth;
        int frameHeight;
        int tileID;
        int positionX;
        int positionY;
        NPC type;
        std::string color;
    };

    struct Item{
        int frameWidth;
        int frameHeight;
        int positionX;
        int positionY;
        std::string typ;
    };

    struct Background{
        std::string filename;
        int scrollspeed;
    };

    struct NPC{
        std::string type;
        std::string move_function;
        signed int move_value;
        unsigned int fireRate;
        signed int speed;
        std::string weapon_type;
        unsigned int weapon_level;

    };

    /**
     * Load XML game information into several structures.
     */
    void load();

    /**
     * Stores game information into XML file.
     */
    void save();

    /**
     * Set XML filename.
     * @param filename XML file for game specification.
     */
    void setFilename(std::string filename) {m_filename = filename;}

    /**
     * Get current name of XML file for game specification.
     * @return XML filename
     */
    std::string getFilename() { return m_filename;}

    std::string getLevelname() { return m_levelname;}

    std::string getTileset() { return m_tileset;}

    Background getBackground() { return m_background;}

    Player getPlayer() { return m_player;}

    int getId() { return m_id;}



private:
    /* XML Filename */
    std::string m_filename;

    /* XML Data Variables */
    int m_id;
    std::string m_levelname;
    std::string m_tileset;
    Background m_background;
    Player m_player;
};

#endif //JUMPER_XML_HPP
