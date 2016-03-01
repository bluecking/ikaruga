#include "Profile.hpp"

Profile::Profile(XML* xmlObject)
{
    this->xmlObject=xmlObject;
    if(xmlObject->profileSize()>0){
        actProfile=xmlObject->getProfile(0);
        actProfileID=0;
    }
    else{
        actProfile.name="FirstProfile";
        actProfile.money=0;
        actProfile.actualWeapon=xmlObject->getWeapon(0);
        std::vector<XML::Profile> profiles;
        profiles.push_back(actProfile);
        xmlObject->setProfiles(profiles);
        actProfileID=0;
        saveActProfile();
    }
}

void Profile::setProfile(std::string profileName){
    std::vector<XML::Profile> profileList=xmlObject->getProfiles();
    for(int i=0;i<profileList.size();i++)
        if(profileList.at(i).name==profileName)
            if(profileList.at(i).name!=profileName){
                xmlObject->setProfile(actProfileID,actProfile);
                actProfile=profileList.at(i);
                xmlObject->saveProfiles();
                break;
            }
}

std::vector<std::string> Profile::getProfiles(){
    std::vector<std::string> profileNameList;
    std::vector<XML::Profile> profileList=xmlObject->getProfiles();
    for(int i=0;i<profileList.size();i++)
        profileNameList.push_back(profileList.at(i).name);
    return profileNameList;
}

void Profile::addHighScore(std::string level,long highscore){
    std::map<std::string,int>::iterator iter = actProfile.highscores.find(level);
    if (iter != actProfile.highscores.end()) {
        if(iter->second<highscore){
            ItemShop::addMoney(highscore-(iter->second));
            iter->second=highscore;
        }
    } else {
        std::pair<std::string,int> pair(level,highscore);
        actProfile.highscores.insert(pair);
        ItemShop::addMoney(highscore);
    }
    saveActProfile();
}

void Profile::saveActProfile(){
    xmlObject->setProfile(actProfileID,actProfile);
    xmlObject->saveProfiles();
}

std::vector<std::pair<std::string,int>> Profile::getHighScores(){
    std::vector<std::pair<std::string,int>> highscores;
    std::pair<std::string,int> highScorePairs;
    BOOST_FOREACH(highScorePairs, actProfile.highscores) {
        highscores.push_back(highScorePairs);
    }
    return highscores;
}
