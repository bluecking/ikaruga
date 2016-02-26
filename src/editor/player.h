#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player
{
public:
    Player();
    std::string filename;
    int frameWidth;
    int frameHeight;
    int positionY;
    std::string stdWeapon;
};

#endif // PLAYER_H
