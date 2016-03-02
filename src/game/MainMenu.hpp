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
#include "Game.hpp"
#include "TexturedLayer.hpp"
#include "../xml/XML.hpp"
#include "RenderTable.hpp"

namespace fs = boost::filesystem;

namespace jumper
{
    class Game;
    class MainWindow;
class MainMenu
{
public:
    MainMenu(MainWindow* win, Game* game, fs::path resDir);

    void update(const Uint8*& currentKeyStates, const bool* keyDown);

private:

    std::vector<fs::path> m_levelFiles;
    MainWindow* m_win;
    fs::path m_resDir;
    Game* m_game;
    TexturedLayer* m_layer;
    Vector2f m_offset;
    SDL_Texture* m_normalFontTexture;
    SDL_Texture* m_selectFontTexture;
    std::vector<std::vector<std::string>> m_tableText;
    std::map<int, boost::filesystem::path> m_levelId_and_path;
    XML m_tmp;
    RenderTable m_table;

    //TODO move to struct?

    void setupBackground(float scrollspeed, string backgroundImage);

    void prepareTable();
};
} //end of namespace jumper

#endif //SCROLLER_MAINMENU_HPP
