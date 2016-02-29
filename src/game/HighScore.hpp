#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <string>
#include "ItemShop.hpp"

class HighScore
{
public:
    HighScore(std::string levelFile);
    void addPointsToHighscore(int points);
    void saveHighscore();
    long getHighscore();
private:
    std::string levelFile;
    long actualHighscore;
};

#endif // HIGHSCORE_H
