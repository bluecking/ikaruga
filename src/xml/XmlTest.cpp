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

        << "Statusbar - filename: " << m_xml.getStatusbar().filename << endl
        << "Statusbar - frameWidth: " << m_xml.getStatusbar().frameWidth << endl
        << "Statusbar - frameHeight: " << m_xml.getStatusbar().frameHeight << endl
        << "Statusbar - letterCount: " << m_xml.getStatusbar().letterCount << endl
        << "Statusbar - capitalOffset: " << m_xml.getStatusbar().capitalOffset << endl
        << "Statusbar - minusculeOffset: " << m_xml.getStatusbar().minusculeOffset << endl
        << "Statusbar - numberOffset: " << m_xml.getStatusbar().numberOffset << endl
        << "Statusbar - offsetToMid: " << m_xml.getStatusbar().offsetToMid << endl

        << "Player - fileName: " << m_xml.getPlayer().filename << endl
        << "Player - numFrames: " << m_xml.getPlayer().numFrames << endl
        << "Player - frameWidth: " << m_xml.getPlayer().frameWidth << endl
        << "Player - frameHeight: " << m_xml.getPlayer().frameHeight << endl
        << "Player - positionX: " << m_xml.getPlayer().positionX << endl
        << "Player - positionY: " << m_xml.getPlayer().positionY << endl
        << "Player - stdWeapon: " << m_xml.getPlayer().stdWeapon << endl
        << "Player - colorOffsetX: " << m_xml.getPlayer().colorOffsetX << endl
        << "Player - colorOffsetY: " << m_xml.getPlayer().colorOffsetY << endl
        << "Player - moveForceX: " << m_xml.getPlayer().moveForceX << endl
        << "Player - moveForceY: " << m_xml.getPlayer().moveForceY << endl
        << "Player - maxVel: " << m_xml.getPlayer().maxVel << endl
        << "Player - fps: " << m_xml.getPlayer().fps << endl << endl;

    for(int i=0;i<(int) m_xml.levelBotSize();i++) {
        XML::LevelBot lBot = m_xml.getLevelBot((unsigned int) i);
        cout << "LevelBot - positionY: " << lBot.positionY << endl
            << "LevelBot - positionX: " << lBot.positionX << endl
            << "LevelBot - color: " << lBot.color << endl
            << "LevelBot - type: " << lBot.type.type << endl
            << "LevelBot - powerUpName: " << lBot.powerUpName << endl
            << "LevelBot - powerUpProb: " << lBot.powerUpProb << endl << endl;
    }
    for(int i=0;i<(int) m_xml.levelItemSize();i++) {
        cout << "LevelItem - type: " << m_xml.getLevelItem(i).type << endl
            << "LevelItem - positionY: " << m_xml.getLevelItem(i).positionY << endl
            << "LevelItem - positionX: " << m_xml.getLevelItem(i).positionX << endl
            << "LevelItem - value: " << m_xml.getLevelItem(i).value << endl << endl;
    }

    m_xml.loadBots("/home/skalbers/Studium/GITHUB_Praktikum/res/advanced_settings/bots.xml");
    m_xml.loadItems("/home/skalbers/Studium/GITHUB_Praktikum/res/advanced_settings/items.xml");
    m_xml.loadWeapons("/home/skalbers/Studium/GITHUB_Praktikum/res/advanced_settings/weapons.xml");

    /** SETTING FILES **/
    for(int i=0;i<(int) m_xml.itemSize();i++) {
        cout << "Item - type: " << m_xml.getItem(i).type << endl
            << "Item - filename: " << m_xml.getItem(i).filename << endl
            << "Item - frameHeight: " << m_xml.getItem(i).frameHeight << endl
            << "Item - frameWidth: " << m_xml.getItem(i).frameWidth << endl << endl;
    }

    for(int i=0;i<(int) m_xml.botSize();i++) {
        cout << "Bot - type: " << m_xml.getBot(i).type << endl
            << "Bot - filename: " << m_xml.getBot(i).filename << endl
            << "Bot - numFrames: " << m_xml.getBot(i).numFrames << endl
            << "Bot - frameHeight: " << m_xml.getBot(i).frameHeight << endl
            << "Bot - frameWidth: " << m_xml.getBot(i).frameWidth << endl
            << "Bot - tileID: " << m_xml.getBot(i).tileID << endl
            << "Bot - colorOffsetX: " << m_xml.getBot(i).colorOffsetX << endl
            << "Bot - colorOffsetY: " << m_xml.getBot(i).colorOffsetY << endl
            << "Bot - fps: " << m_xml.getBot(i).fps << endl
            << "Bot - NPC - type: " << m_xml.getBot(i).npc.type << endl
            << "Bot - NPC - move_function: " << m_xml.getBot(i).npc.move_function << endl
            << "Bot - NPC - move_value: " << m_xml.getBot(i).npc.move_value << endl
            << "Bot - NPC - speed: " << m_xml.getBot(i).npc.speed << endl
            << "Bot - NPC - stdWeapon: " << m_xml.getBot(i).npc.stdWeapon << endl << endl;
    }

    for(int i=0;i<(int) m_xml.weaponSize();i++) {
        cout << "Weapon - type: " << m_xml.getWeapon(i).type << endl
            << "Weapon - filename: " << m_xml.getWeapon(i).filename << endl
            << "Weapon - colorOffsetX: " << m_xml.getWeapon(i).colorOffsetX << endl
            << "Weapon - colorOffsetY: " << m_xml.getWeapon(i).colorOffsetY << endl;
    }

    m_xml.setFilename("/tmp/scrollerXmlOut.xml");
    m_xml.save();

    return 0;
}
