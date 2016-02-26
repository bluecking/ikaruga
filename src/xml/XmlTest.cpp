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

    XML m_xml(argv[1]);

    cout << "Parsing level defintion (xml):" << endl
        << "ID: " << m_xml.getId() << endl
        << "Levelname: " << m_xml.getLevelname() << endl
        << "Tileset: " << m_xml.getTileset() << endl
        << "Background - filename: " << m_xml.getBackground().filename << endl
        << "Background - Scrollspeed: " << m_xml.getBackground().scrollspeed << endl
        << "Player - fileName: " << m_xml.getPlayer().filename << endl
        << "Player - frameWidth: " << m_xml.getPlayer().frameWidth << endl
        << "Player - frameHeight: " << m_xml.getPlayer().frameHeight << endl
        << "Player - positionY: " << m_xml.getPlayer().positionY << endl
        << "Player - stdWeapon: " << m_xml.getPlayer().stdWeapon << endl << endl;

    for(int i=0;i<(int) m_xml.levelBotSize();i++) {
        XML::LevelBot lBot = m_xml.getLevelBot((unsigned int) i);
        cout << "Bot - positionY: " << lBot.positionY << endl
            << "Bot - positionX: " << lBot.positionX << endl
            << "Bot - color: " << lBot.color << endl
            << "Bot - type: " << lBot.type.type << endl
            << "Bot - powerUpName: " << lBot.powerUpName << endl
            << "Bot - powerUpProb: " << lBot.powerUpProb << endl;
    }
    for(int i=0;i<(int) m_xml.levelItemSize();i++) {
        cout << "Item - type: " << m_xml.getLevelItem(i).type << endl
            << "Item - positionY: " << m_xml.getLevelItem(i).positionY << endl
            << "Item - positionX: " << m_xml.getLevelItem(i).positionX << endl
            << "Item - value: " << m_xml.getLevelItem(i).value << endl;
    }

    m_xml.setFilename("/tmp/scrollerXmlOut.xml");
    m_xml.save();

    return 0;
}
