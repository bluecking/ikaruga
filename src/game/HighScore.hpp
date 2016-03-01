#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <string>
#include "ItemShop.hpp"
#include "Profile.hpp"

class HighScore
{
public:
    HighScore(Profile* profile,std::string levelFile);
    void addPointsToHighscore(int points);
    void saveHighscore();
    long getHighscore();
private:
    std::string levelFile;
    long actualHighscore;
    Profile* profile;
};

#endif // HIGHSCORE_H
