#include "HighScore.hpp"

jumper::HighScore::HighScore(Profile* profile,std::string levelFile)
{
    this->levelFile=levelFile;
    this->actualHighscore=0;
}

void jumper::HighScore::addPointsToHighscore(int points){
    this->actualHighscore+=points;
}

void jumper::HighScore::saveHighscore(){
    profile->addHighScore(levelFile,actualHighscore);
}

long jumper::HighScore::getHighscore(){
    return this->actualHighscore;
}
