#include "HighScore.hpp"

HighScore::HighScore(Profile* profile,std::string levelFile)
{
    this->levelFile=levelFile;
    this->actualHighscore=0;
}

void HighScore::addPointsToHighscore(int points){
    this->actualHighscore+=points;
}

void HighScore::saveHighscore(){
    profile->addHighScore(levelFile,actualHighscore);
}

long HighScore::getHighscore(){
    return this->actualHighscore;
}
