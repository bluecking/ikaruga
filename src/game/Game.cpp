/*
 * Game.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: twiemann
 */

#include "Game.hpp"
#include "PuzzleBox.hpp"
#include "KillAnimation.hpp"

#include <iostream>
#include <algorithm>
#include <set>
#include <string>

using std::set;
using std::cout;
using std::endl;

namespace jumper
{

    Game::Game(MainWindow* mainWindow)
    {
        m_player = 0;
        m_level = 0;
        m_layer = 0;
        m_renderer = mainWindow->getRenderer();
        m_statusBar = 0;

        m_windowWidth = mainWindow->w();
        m_windowHeight = mainWindow->h();

        m_started = false;
        m_startTicks = 0;

        SDL_SetRenderDrawColor(m_renderer, 0, 102, 204, 255);
    }

    Game::~Game()
    {
        // TODO Auto-generated destructor stub
        m_sound.stop();
    }

    void Game::setPlayer(Player* player)
    {
        m_player = player;
        m_actors.push_back(player);
        m_renderables.push_back(player);
    }

    void Game::setLevel(Level* level)
    {
        m_level = level;
        m_renderables.push_back(level);

        std::size_t found = m_level->getPath().find_last_of("/\\");
        string sound_path = m_level->getPath().substr(0,found);
        found = sound_path.find_last_of("/\\");
        sound_path = sound_path.substr(0,found);
        sound_path += "/sounds/game_loop.wav";
        std::cout << sound_path + "\n";
        m_sound = Sound(sound_path);
    }

    Level* Game::getLevel()
    {

        return m_level;

    }

    void Game::addActor(Actor* actor)
    {
        m_actors.push_back(actor);
        m_renderables.push_back(actor);
    }

    void Game::update(const Uint8*& currentKeyStates, const bool* keyDown)
    {
        if (m_started)
        {
            // react to color change
            if (keyDown[SDL_SCANCODE_C])
            {
                m_player->toggleColor();
            }

            // react to shoot
            if (currentKeyStates[SDL_SCANCODE_SPACE])
            {
                m_player->shoot();
            }

            //Update Statusbar \o/
            m_statusBar->setWeaponName(m_player->getWeapon()->getWeaponName());
            m_statusBar->setEvolutionStage(std::to_string(m_player->getWeapon()->getEvolutionStage()));
            m_statusBar->setHealth(m_player->getHealth());
            // react to move input
            Vector2f moveDirection(0, 0);
            if (currentKeyStates[SDL_SCANCODE_UP])
            {
                moveDirection.setY(-1);
            }
            if (currentKeyStates[SDL_SCANCODE_DOWN])
            {
                moveDirection.setY(1);
            }
            if (currentKeyStates[SDL_SCANCODE_LEFT])
            {
                moveDirection.setX(-1);
            }
            if (currentKeyStates[SDL_SCANCODE_RIGHT])
            {
                moveDirection.setX(1);
            }
            m_player->setMoveDirection(moveDirection);

            moveActors();
            scrollHorizontal();
            checkPlayerCollision();
            checkCameraCollision();
            removeProjectiles();

            SDL_RenderClear(m_renderer);

            if (m_layer)
            {
                m_layer->render();
            }

            /*
             * You have to render the Statusbar AFTER the tiles, so the thing is always on Top
             */
            for (size_t i = 0; i < m_renderables.size(); i++)
            {
                m_renderables[i]->render();
            }

            if (m_statusBar)
            {
                m_statusBar->setScore(m_player->physics().position().x());
                m_statusBar->render();
            }

            // Update screen
            SDL_RenderPresent(m_renderer);
        }
    }

    void Game::removeActor(Actor* a)
    {
        auto it = std::find(m_actors.begin(), m_actors.end(), a);
        m_actors.erase(it);

        auto it2 = std::find(m_renderables.begin(), m_renderables.end(), a);
        m_renderables.erase(it2);
    }

    void Game::checkPlayerCollision()
    {
        set<Actor*> to_remove;
        KillAnimation* anim = 0;
        for (auto it = m_actors.begin(); it != m_actors.end(); it++)
        {
            Actor* a = *it;
            if (a->getHealth() <= 0)
            {
                to_remove.insert(a);
            }

            // Check for self collision
            if (a != m_player)
            {
                Collision c = m_player->getCollision(*a);

                // Simple items can be collected on the fly
                if (a->type() == ITEM && c.type() != NONE)
                {
                    to_remove.insert(a);
                }

                // If an collection with an enemy occured, check
                // who killed whom (Player only can kill enemies
                // when falling down.
                if (a->type() == ENEMY && c.type() != NONE)
                {
                    if (c.type() == BOOM)
                    {
                        cout << "PLAYER KILLED" << endl;
                    }
                    else if (c.type() == DOWN)
                    {
                        to_remove.insert(a);
                        anim = new KillAnimation(a);
                    }
                }

                if (a->type() == PUZZLEBOX)
                {
                    PuzzleBox* b = static_cast<PuzzleBox*>(a);
                    m_player->resolveCollision(*a);
                    if (c.type() == UP)
                    {
                        b->setHit(true);
                    }
                }
            }
        }

        // Remove actors that were killed in this loop. We have to
        // store them separately because otherwise we would corrupt
        // to loop structure
        for (auto i = to_remove.begin(); i != to_remove.end(); i++)
        {
            removeActor(*i);
        }

        if (anim)
        {
            m_renderables.push_back(anim);
        }
    }

    // This method corrects the position of the player, if its leaving the borders of the camera.
    // It is invoked by Game::update()
    void Game::checkCameraCollision()
    {
        float leftBorder, topBorder, rightBorder, bottomBorder = 0;
        float borderOffsetInPixel = Renderable::m_camera.getBorderOffset();

        leftBorder = Renderable::m_camera.x() + borderOffsetInPixel;
        topBorder = Renderable::m_camera.y() + borderOffsetInPixel;
        rightBorder = Renderable::m_camera.x() + Renderable::m_camera.w() - borderOffsetInPixel;
        bottomBorder = Renderable::m_camera.y() + Renderable::m_camera.h() - borderOffsetInPixel;

        // Player leaves top border of the camera
        if (m_player->position().y() <= topBorder)
        {
            m_player->setPosition(Vector2f(m_player->position().x(), topBorder));
        }

        // Player leaves left border of the camera
        if (m_player->position().x() <= leftBorder)
        {
            m_player->setPosition(Vector2f(leftBorder, m_player->position().y()));
        }

        // Player leaves right border of the camera
        if (m_player->position().x() + m_player->w() >= rightBorder)
        {
            m_player->setPosition(Vector2f(rightBorder - m_player->w(), m_player->position().y()));
        }

        // Player leaves bottom border of the camera
        if (m_player->position().y() + m_player->h() >= bottomBorder)
        {
            m_player->setPosition(Vector2f(m_player->position().x(), bottomBorder - m_player->h()));
        }
    }

    void Game::moveActors()
    {
        for (auto it = m_actors.begin(); it != m_actors.end(); it++)
        {
            (*it)->move(*m_level);
        }
    }

    void Game::start()
    {
        m_sound.play();
        m_started = true;
    }

    void Game::scrollHorizontal()
    {
        float dt = getElapsedTime();

        Vector2f scrollOffset(m_level->physics().getScrollingSpeed() * dt);
        m_player->setPosition(m_player->position() +
                              m_level->collide(m_player->position(), m_player->w(), m_player->h(), scrollOffset));
        Renderable::m_camera.move(Renderable::m_camera.position() + scrollOffset);
    }

    float Game::getElapsedTime()
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

    void Game::removeProjectiles()
    {
        set<Actor*> to_remove;
        for (auto it = m_actors.begin(); it != m_actors.end(); it++)
        {
            Actor* a = *it;

            if (a->type() == PROJECTILE)
            {
                if (!a->visible())
                {
                    to_remove.insert(a);
                }
            }
        }

        // Remove actors that were killed in this loop. We have to
        // store them separately because otherwise we would corrupt
        // to loop structure
        for (auto i = to_remove.begin(); i != to_remove.end(); i++)
        {
            removeActor(*i);
        }
    }
} /* namespace jumper */
