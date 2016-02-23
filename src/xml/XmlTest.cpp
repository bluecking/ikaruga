#include <ostream>
#include <iostream>
#include "XML.hpp"

using std::cout;
using std::endl;

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

    cout << "ID: " << m_xml.getId() << endl
        << "Levelname: " << m_xml.getLevelname() << endl
        << "Tileset: " << m_xml.getTileset() << endl
        << "Background: " << m_xml.getBackground().filename << endl
        << "Scrollspeed: " << m_xml.getBackground().scrollspeed << endl
        << "Player - fileName: " << m_xml.getPlayer().filename << endl
        << "Player - frameWidth: " << m_xml.getPlayer().frameWidth << endl
        << "Player - frameHeight: " << m_xml.getPlayer().frameHeight << endl
        << "Player - positionY: " << m_xml.getPlayer().positionY << endl
        << "Player - stdWeapon: " << m_xml.getPlayer().stdWeapon << endl;
//    for(int i=0;i<m_xml.getBots().size();i++) {
//        cout << "Bot - fileName: " << m_xml.getBots(). << endl
//            << "Bot - frameWidth: " << m_xml.getBots(). << endl
//            << "Bot - frameHeight: " << m_xml.getBots(). << endl
//            << "Bot - tileID: " << m_xml.getBots(). << endl
//            << "Bot - positionX: " << m_xml.getBots(). << endl
//            << "Bot - positionY: " << m_xml.getBots(). << endl
//            << "Bot - npc: " << m_xml.getBots(). << endl
//            << "Bot - color: " << m_xml.getBots(). << endl;
//    }
}