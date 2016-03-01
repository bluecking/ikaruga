#ifndef PROFILE_H
#define PROFILE_H
#include <string>
#include <vector>
#include <iostream>
#include "../xml/XML.hpp"
#include "ItemShop.hpp"
#include <boost/foreach.hpp>
class Profile
{
public:
    Profile(XML* xmlObject);
    std::vector<std::string> getProfiles();
    void setProfile(std::string profileName);
    void addHighScore(std::string level,long highscore);
    std::vector<std::pair<std::string,int>> getHighScores();
private:
    XML::Profile actProfile;
    void saveActProfile();
    XML* xmlObject;
    int actProfileID;
};

#endif // PROFILE_H
