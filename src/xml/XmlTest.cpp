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
        << "Background - filename: " << m_xml.getBackground().filename << endl
        << "Background - Scrollspeed: " << m_xml.getBackground().scrollspeed << endl
        << "Player - fileName: " << m_xml.getPlayer().filename << endl
        << "Player - frameWidth: " << m_xml.getPlayer().frameWidth << endl
        << "Player - frameHeight: " << m_xml.getPlayer().frameHeight << endl
        << "Player - positionY: " << m_xml.getPlayer().positionY << endl
        << "Player - stdWeapon: " << m_xml.getPlayer().stdWeapon << endl;
}


<background filename="background_40x40.png">
                                       <scrollspeed>3</scrollspeed>
</background>
<player filename="player_combined_47x51.png">
                 <frameWidth>18</frameWidth>
<frameHeight>32</frameHeight>
<positionY>40</positionY>
<stdWeapon>LaserGun</stdWeapon>
</player>
<bot filename="enemys.png">
              <frameWidth>18</frameWidth>
<frameHeight>32</frameHeight>
<tileID>1</tileID>
<positionX>410</positionX>
<positionY>40</positionY>
<npc type="Bot">
          <move function="sin">3</move>
<fireRate>16</fireRate>
<speed>-2</speed>
<weapon type="laser">1</weapon>
</npc>
<color>red</color>
</bot>
<bot filename="enemys.png">
              <frameWidth>18</frameWidth>
<frameHeight>32</frameHeight>
<tileID>5</tileID>
<positionX>100</positionX>
<positionY>50</positionY>
<npc type="Boss">
          <move function="sin">0</move>
<fireRate>16</fireRate>
<speed>-2</speed>
<weapon type="laser">0</weapon>
</npc>
<color>blue</color>
</bot>
<item filename="powerups_20x20_transparent.png">
               <frameWidth>18</frameWidth>
<frameHeight>32</frameHeight>
<positionX>40</positionX>
<positionY>30</positionY>
<type>laser</type>
</item>
</level>