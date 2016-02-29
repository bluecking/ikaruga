#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <string>

class HighScore
{
public:
    HighScore(std::string levelFile);
private:
    std::string levelFile;
    long actualHighscore;
};

#endif // HIGHSCORE_H
