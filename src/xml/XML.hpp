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
        int frameWidth;
        int frameHeight;
        int posY;
        std::string stdWeapon;
    };

    struct Bot{
        int frameWidth;
        int frameHeight;
        int posX;
        int posY;
        std::string typ;
        std::string color;
    };

    struct Item{
        int frameWidth;
        int frameHeight;
        int posX;
        int posY;
        std::string typ;
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

    int getId() { return m_id;}



private:
    std::string m_filename;
    std::string m_levelname;
    int m_id;

};

#endif //JUMPER_XML_HPP
