#include "HighScore.hpp"

HighScore::HighScore(std::string levelFile)
{
    this->levelFile=levelFile;
    this->actualHighscore=0;
}

void HighScore::addPointsToHighscore(int points){
    this->actualHighscore+=points;
}

void HighScore::saveHighscore(){
    long oldHighscore=0;
    //lade HighScore von XML
    if(this->actualHighscore>oldHighscore){
        //saveNewHighscore
        ItemShop::addMoney(this->actualHighscore-oldHighscore);
    }
}

long HighScore::getHighscore(){
    return this->actualHighscore;
}
