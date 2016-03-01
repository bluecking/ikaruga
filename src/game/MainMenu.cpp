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



std::vector<fs::path> MainMenu::findFiles(const fs::path& path,
                                          boost::regex pattern)
{
    std::vector<fs::path> vec;
    if (!fs::is_directory(path)) //!path.empty()
    {throw std::invalid_argument("You have to provide a resource DIRECTORY!");}

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
            //std::cout << i->path().filename().string() << std::endl; //Debug output
        }
    return vec;
}


    MainMenu::MainMenu(MainWindow* win, fs::path resDir, Game game) :
    m_win(win), m_resDir(resDir), m_game(game)
    {
        m_levelFiles = findFiles(resDir, boost::regex("^.*\\.xml$"));
    }

    void MainMenu::update(const Uint8*& currentKeyStates, const bool* keyDown)
    {
        //TODO display menu



        Game::setupGame(m_resDir.path().filename().string() + "/levels/level0.xml", m_win, m_game );
        m_win->setGame(m_game);
        m_game->start();
    }
} //end of namespace jumper