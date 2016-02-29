#include "HighScore.hpp"

HighScore::HighScore(QString levelFile)
{
    this->levelFile=levelFile;
    this->actualHighscore=0;
}

HighScore::addPointsToHighscore(int points){
    this->actualHighscore+=points;
}

HighScore::saveHighscore(){
    long oldHighscore=0;
    //lade HighScore von XML
    if(this->actualHighscore>oldHighscore){

    }
}
