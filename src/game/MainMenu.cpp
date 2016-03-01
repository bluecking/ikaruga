/**
* @file MainMenu.cpp
* @brief Implementation of MainMenu
*
* @author Patrick Steinforth (psteinforth@uni-osnabrueck.de)
* @date 29 Feb 2016
*/
#include "MainMenu.hpp"
#include "Filesystem.hpp"

namespace jumper
{


    MainMenu::MainMenu(MainWindow* win, Game* game, fs::path resDir) :
    m_win(win), m_resDir(resDir), m_game(game)
    {
        m_levelFiles = Filesystem::findFiles(resDir, boost::regex("^.*\\.xml$"));
    }

    void MainMenu::update(const Uint8*& currentKeyStates, const bool* keyDown)
    {
        //TODO display menu



//---------------------------------------------------------------------------------------------
    //std::string new_filename = m_resDir.f + ".foo";
    //p.remove_leaf() /= new_filename;
    Game::setupGame(m_resDir.string() + "/levels/level0.xml", m_win, m_game );//TODO change to specific level
    m_win->setGame(m_game);
    m_win->setActualScreen(MainWindow::RENDER_GAME);
    m_game->start();

    }

    //Creates the Levelbackground
    void MainMenu::setupBackground(XML::Background background, std::string filepath)
    {
        SDL_Texture* texture = TextureFactory::instance(m_win->getRenderer()).getTexture(filepath + background.filename);
        float scrollspeed = background.scrollspeed * 1.0f;
        TexturedLayer* layer = new TexturedLayer(w->getRenderer(), texture, game->getLevel()->tileHeight());

        layer->setScrollSpeed(scrollspeed);
        game->setSound(filepath + background.soundfile, background.volume);
        game->setLayer(layer);
    }






} //end of namespace jumper