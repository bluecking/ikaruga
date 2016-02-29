/**
* @file MainMenu.cpp
* @brief Implementation of MainMenu
*
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
* @date 29 Feb 2016
*/
#include "MainMenu.hpp"

namespace jumper
{

std::vector<fs::path> MainMenu::get_levels(const fs::path & path,
                                    boost::regex pattern)
{
    std::vector<fs::path> vec;
    if (!fs::is_directory(path)) //!path.empty()
    {throw std::invalid_argument("You have to provide a resource directory!");}

        fs::directory_iterator end; //default construction yields past-the-end

        for (fs::directory_iterator i(path); i != end; ++i, !path.empty())
        {
            // Skip if not a file
            if( !boost::filesystem::is_regular_file( i->status() ) ) continue;

            boost::smatch match_result;

            // Skip if no match for V2:
            //if( !boost::regex_match(i->leaf(), match_result, pattern ) ) continue;
            // For V3:
            if(!boost::regex_match(i->path().filename().string(), match_result, pattern)) continue;

            // File matches, store it
            vec.push_back( i->path().filename() );
        }
    return vec;
}


} //end of namespace jumper