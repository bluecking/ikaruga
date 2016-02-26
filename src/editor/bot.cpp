#include "bot.h"

Bot::Bot()
{
    NPC *npc=new NPC();
    this->npc=npc;
    this->color="RED";
    this->filename="?";
    this->frameHeight=40;
    this->frameWidth=40;
    this->positionX=0;
    this->positionY=0;
    this->tileID=0;
    npc->fireRate=0.2;
    this->npc->move_function="SIN";
    this->npc->move_value=0;
    this->npc->speed=100;
    this->npc->type="Normal";
    this->npc->weapon_level=1;
    this->npc->weapon_type="LaserWeapon";
}
