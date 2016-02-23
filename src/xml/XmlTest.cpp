#include <ostream>
#include <iostream>
#include "XML.hpp"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Please specify a level definition (xml)." << std::endl;
        return -1;
    }

    XML m_xml;
    m_xml.setFilename(argv[1]);
    m_xml.load();

    std::cout << "ID: " << m_xml.getId() << std::endl
        << "Levelname: " << m_xml.getLevelname() << std::endl
        << "Tileset: " << m_xml.getTileset() << std::endl
        << "Background: " << m_xml.getBackground().filename << std::endl
        << "Scrollspeed: " << m_xml.getBackground().scrollspeed << std::endl
        << "Player: " << m_xml.getPlayer().filename << std::endl
        << "Player - frameWidth: " << m_xml.getPlayer().frameWidth << std::endl
        << "Player - frameHeight: " << m_xml.getPlayer().frameHeight << std::endl
        << "Player - positionY: " << m_xml.getPlayer().positionY << std::endl
        << "Player - stdWeapon: " << m_xml.getPlayer().stdWeapon << std::endl
        ;
}