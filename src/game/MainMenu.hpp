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
#include <SDL_stdinc.h>
#include "MainWindow.hpp"

namespace fs = boost::filesystem;

namespace jumper
{
class MainMenu {
public:
    MainMenu(MainWindow* win, Game* game, fs::path resDir);

    void update(const Uint8*& currentKeyStates, const bool* keyDown);

private:
    /**
     * Searches files within a directory that match a regex pattern.
     * @param path The directory path.
     * @param pattern Regex pattern.
     * @return All files within the given path that match the pattern.
     */
    std::vector<fs::path> findFiles(const fs::path& path,
                                    boost::regex pattern);

    std::vector<fs::path> m_levelFiles;
    MainWindow* m_win;
    fs::path m_resDir;
    Game* m_game;
};
} //end of namespace jumper

#endif //SCROLLER_MAINMENU_HPP
