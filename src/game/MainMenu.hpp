/**
* @file MainMenu.hpp
* @brief Definition of MainMenu
*
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
* @date 29 Feb 2016
*/
#ifndef SCROLLER_MAINMENU_HPP
#define SCROLLER_MAINMENU_HPP

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/regex.hpp>

namespace fs = boost::filesystem;

namespace jumper
{
class MainMenu {

    std::vector<fs::path> get_levels(const fs::path & path,
                                     boost::regex pattern);
};
} //end of namespace jumper

#endif //SCROLLER_MAINMENU_HPP
