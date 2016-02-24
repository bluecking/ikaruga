#ifndef BOT_H
#define BOT_H
#include <string>

class Bot
{
public:
    class NPC{
        public:
            std::string type;
            std::string move_function;
            signed int move_value;
            unsigned int fireRate;
            signed int speed;
            std::string weapon_type;
            unsigned int weapon_level;
    };
    Bot();
    std::string filename;
    int frameWidth;
    int frameHeight;
    int tileID;
    int positionX;
    int positionY;
    NPC npc;
    std::string color;
};

#endif // BOT_H
