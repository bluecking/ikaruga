#ifndef ITEM_H
#define ITEM_H
#include <string>

class Item
{
public:
    Item();
    std::string filename;
    int frameWidth;
    int frameHeight;
    int positionX;
    int positionY;
    std::string type;
};

#endif // ITEM_H
