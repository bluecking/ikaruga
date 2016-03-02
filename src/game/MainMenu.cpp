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
            m_win(win), m_resDir(resDir), m_game(game), m_table(NULL, NULL, NULL, NULL)
    {
        boost::filesystem::path concat(resDir);
        concat /= "levels";
        m_levelFiles = Filesystem::findFiles(concat, boost::regex("^.*\\.xml$"));

        setupBackground(1.0f, m_resDir.string() + "/images/star_background_2_200x200.png");
        m_normalFontTexture = TextureFactory::instance(m_win->getRenderer()).getTexture(
                m_resDir.string() + "/images/font_white_20x20.png"); //TODO make dynamic
        m_selectFontTexture = TextureFactory::instance(m_win->getRenderer()).getTexture(
                m_resDir.string() + "/images/font_blue_20x20.png"); //TODO make dynamic

        m_table = RenderTable(m_win->getRenderer(), m_normalFontTexture, 20,
                              20); //TODO static tile height&width -> make dynamic
        prepareTable();
        m_table.setStringProperties(2, 1, 0, m_tableText);
        RenderTable::tableProperties tableProps;
        tableProps.positionX = 50;
        tableProps.positionY = 120;
        tableProps.width = 200;
        tableProps.height = 100;
        m_table.setTableProperties(tableProps);
    }

    void MainMenu::update(const Uint8*& currentKeyStates, const bool* keyDown)
    {
        if (m_win->getActualScreen() == m_win->RENDER_MAINMENU)
        {
            //Render background
            m_offset.setX(0.005f);
            m_offset.setY(0.005f);
            m_layer->setScrollSpeed(100.0f);
            m_layer->m_camera.move(m_layer->m_camera.position() + m_offset);

            SDL_RenderClear(m_win->getRenderer());
            m_layer->render();

            //Render table
            if (keyDown[SDL_SCANCODE_UP])
            {
                m_table.increase();
            }

            if (keyDown[SDL_SCANCODE_DOWN])
            {
                m_table.decrease();
            }
            m_table.render();
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

    void MainMenu::prepareTable()
    {
        for (int i = 0; i < m_levelFiles.size(); i++)
        {
            try
            {
                XML m_tmp(m_levelFiles[i].string());
                m_tableText.resize(m_tableText.size() + 1);
                m_levelId_and_path.insert(std::pair<int, boost::filesystem::path>(m_tmp.getId(), m_levelFiles[i]));
                m_tableText[m_tableText.size() - 1].resize(1);
                m_tableText[m_tableText.size() - 1][0] = m_tmp.getLevelname();
            }
            catch (...)
            {
                std::cerr << "Failed to read file " + m_levelFiles[i].string() << std::endl;
                continue;
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

} //end of namespace jumper