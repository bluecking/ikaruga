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
    for(int i=0;i<(int) m_xml.getBots().size();i++) {
        cout << "Bot - fileName: " << m_xml.getBots()[i].filename << endl
            << "Bot - frameWidth: " << m_xml.getBots()[i].frameWidth << endl
            << "Bot - frameHeight: " << m_xml.getBots()[i].frameHeight << endl
            << "Bot - tileID: " << m_xml.getBots()[i].tileID << endl
            << "Bot - positionX: " << m_xml.getBots()[i].positionX << endl
            << "Bot - positionY: " << m_xml.getBots()[i].positionY << endl
            << "Bot - color: " << m_xml.getBots()[i].color << endl
            << "Bot - NPC - type: " << m_xml.getBots()[i].npc.type << endl
            << "Bot - NPC - move_function: " << m_xml.getBots()[i].npc.move_function << endl
            << "Bot - NPC - move_value: " << m_xml.getBots()[i].npc.move_value << endl
            << "Bot - NPC - fireRate: " << m_xml.getBots()[i].npc.fireRate << endl
            << "Bot - NPC - speed: " << m_xml.getBots()[i].npc.speed << endl
            << "Bot - NPC - weapon_type: " << m_xml.getBots()[i].npc.weapon_type << endl
            << "Bot - NPC - weapon_level: " << m_xml.getBots()[i].npc.weapon_level << endl << endl;
    }
    for(int i=0;i<(int) m_xml.getItems().size();i++) {
        cout << "Item - fileName: " << m_xml.getItems()[i].filename << endl
            << "Item - frameWidth: " << m_xml.getItems()[i].frameWidth << endl
            << "Item - frameHeight: " << m_xml.getItems()[i].frameHeight << endl
            << "Item - positionX: " << m_xml.getItems()[i].positionX << endl
            << "Item - positionY: " << m_xml.getItems()[i].positionY << endl
            << "Item - type: " << m_xml.getItems()[i].type;
    }

    cout << endl << "Bot 1 : " << endl;
    XML::Bot b1 = m_xml.getBot(1);
    cout << "Bot - fileName: " << b1.filename << endl
        << "Bot - frameWidth: " << b1.frameWidth << endl
        << "Bot - frameHeight: " << b1.frameHeight << endl
        << "Bot - tileID: " << b1.tileID << endl
        << "Bot - positionX: " << b1.positionX << endl
        << "Bot - positionY: " << b1.positionY << endl
        << "Bot - color: " << b1.color << endl
        << "Bot - NPC - type: " << b1.npc.type << endl
        << "Bot - NPC - move_function: " << b1.npc.move_function << endl
        << "Bot - NPC - move_value: " << b1.npc.move_value << endl
        << "Bot - NPC - fireRate: " << b1.npc.fireRate << endl
        << "Bot - NPC - speed: " << b1.npc.speed << endl
        << "Bot - NPC - weapon_type: " << b1.npc.weapon_type << endl
        << "Bot - NPC - weapon_level: " << b1.npc.weapon_level;

    m_xml.save();
}
