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

        setupBackground(1.0f, m_resDir.string() + "/images/star_background_2_200x200.png");
        m_startTicks = 0;
    }

    void MainMenu::update(const Uint8*& currentKeyStates, const bool* keyDown)
    {
        if(m_win->getActualScreen() == m_win->RENDER_MAINMENU)
        {

            SDL_RenderClear(m_win->getRenderer());
            moveBackground();

            //TODO display menu

            SDL_RenderPresent(m_win->getRenderer());

            //temporary to start game -------------------------------------------------------------------
            if (currentKeyStates[SDL_SCANCODE_G])
            {
                Game::setupGame(m_resDir.string() + "/levels/level0.xml", m_win, m_game);
                m_win->setGame(m_game);
                m_win->setActualScreen(MainWindow::RENDER_GAME);
                m_game->start();
            }
        }
    }

    //Creates the highscore background
    void MainMenu::setupBackground(float scrollspeed, std::string backgroundImage)
    {
        SDL_RenderClear(m_win->getRenderer());
        SDL_Texture* texture = TextureFactory::instance(m_win->getRenderer()).getTexture(backgroundImage);
        m_layer = new TexturedLayer(m_win->getRenderer(), texture, 1);
        //m_game->setSound(filepath + background.soundfile, background.volume);
    }

    void MainMenu::moveBackground()
    {
        float dt = getElapsedTime();
        m_offset.setX(1.0f * dt);
        m_offset.setY(1.0f * dt);
        m_layer->setScrollSpeed(100.0f);
        m_layer->m_camera.move(m_layer->m_camera.position() + m_offset);
        m_layer->render();
    }

    float MainMenu::getElapsedTime()
    {
        if (m_startTicks == 0)
        {
            m_startTicks = SDL_GetTicks();
        }
        Uint32 ticks = SDL_GetTicks();
        float time = (ticks - m_startTicks) / 1000.0f;
        m_startTicks = ticks;
        return time;
    }




} //end of namespace jumper