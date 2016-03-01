/*
 * Game.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: twiemann
 */

#include "MainWindow.hpp"
#include "Game.hpp"
#include "CollisionManager.hpp"
#include "Filesystem.hpp"

#include <set>
using std::set;
using std::cout;
using std::endl;

namespace jumper
{

void Game::getPlayerProperty(XML::Player player, PlayerProperty& p)
{
    int pos_x = player.positionX;
    int pos_y = player.positionY;
    float moveForceX = player.moveForceX * 1.0;
    float moveForceY = player.moveForceY * 1.0;
    float maxVelRun = player.maxVel * 1.0;

    p.setPosition(Vector2f(pos_x, pos_y));
    p.setMoveForce(Vector2f(moveForceX, moveForceY));
    p.setMaxRunVelocity(maxVelRun);
}

void Game::getBotProperty(XML::LevelBot bot, PlayerProperty& p)
{
    int pos_x = bot.positionX;
    int pos_y = bot.positionY;
    float moveForceX = 1.0;
    float moveForceY = 1.0;
    float maxVelRun = 1.0;

    p.setPosition(Vector2f(pos_x, pos_y));
    p.setMoveForce(Vector2f(moveForceX, moveForceY));
    p.setMaxRunVelocity(maxVelRun);
}


//create level
void Game::setupLevel(MainWindow* w, Game* game, std::string filepath)
{
    Level* level = new Level(w->getRenderer(), filepath);
    game->setLevel(level);
}

//Creates the Levelbackground
    void Game::setupBackground(XML::Background background, std::string filepath, MainWindow* w, Game* game)
    {
        SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(filepath + background.filename);
        float scrollspeed = background.scrollspeed * 1.0f;
        TexturedLayer* layer = new TexturedLayer(w->getRenderer(), texture, game->getLevel()->tileHeight());

        layer->setScrollSpeed(scrollspeed);
        game->setSound(filepath + background.soundfile, background.volume);
        game->setLayer(layer);
    }

//create statusbar
    void Game::setupStatusbar(MainWindow* w, Game* game, XML::Statusbar statusbar, std::string filepath)
    {
        SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(filepath + statusbar.filename);

        StatusBar* bar = new StatusBar(w->getRenderer(), texture, statusbar.frameWidth, statusbar.frameHeight,
                                       statusbar.capitalOffset,
                                       statusbar.minusculeOffset, statusbar.numberOffset, statusbar.letterCount,
                                       statusbar.offsetToMid);


        int yStart = w->h() - (game->getLevel()->levelHeight() * game->getLevel()->tileHeight());

        int xEnd = w->w() - 1;
        bar->setPosition(Vector2i(0, yStart), Vector2i(xEnd, 0));
        game->setStatusBar(bar);
    }

//create Player
    void Game::setupPlayer(XML::Player xplayer, MainWindow* w, Game* game, std::string filepath)
    {
        SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(filepath + xplayer.filename);
        Player* player = new Player(w->getRenderer(), texture, xplayer.frameWidth, xplayer.frameHeight, xplayer.numFrames, xplayer.health, xplayer.collisionDamage);
        player->setExplosionSound(filepath + xplayer.explosionSoundFile);
        player->setHitMarkSound(filepath + xplayer.hitSoundFile);
        player->setHitMarkVolume(xplayer.hitVolume);

        // set weapon
        XML::Weapon weapon = xplayer.stdWeapon;
        Vector2i* textureSize = new Vector2i(weapon.frameWidth, weapon.frameHeight);
        Vector2f* weaponOffset = new Vector2f(weapon.weaponOffsetX, weapon.weaponOffsetY);
        Vector2f* projectileColorOffset = new Vector2f(weapon.colorOffsetX, weapon.colorOffsetY);
        float coolDown = weapon.cooldown;
        SDL_Texture* weaponTexture = TextureFactory::instance(w->getRenderer()).getTexture(
                filepath + weapon.filename);

        player->setWeapon(
                new LaserWeapon(*game,
                                *player,
                                weaponTexture,
                                *textureSize,
                                *weaponOffset,
                                *projectileColorOffset,
                                coolDown,
                                filepath + weapon.soundfile,
                                weapon.shootingVolume,
                                weapon.collisionDamage));


        game->setPlayer(player);
        player->setFocus(true);

        PlayerProperty p;
        getPlayerProperty(xplayer, p);
        player->setPhysics(p);
        player->setFPS(xplayer.fps);

        float colorOffsetX = xplayer.colorOffsetX;
        float colorOffsetY = xplayer.colorOffsetY;
        Vector2f colorOffset(colorOffsetX, colorOffsetY);
        player->setColorOffset(colorOffset);
    }



//create Bots
    void Game::setupBots(vector<XML::LevelBot> bots, MainWindow* w, Game* game, std::string filepath)
    {
        for (auto it = bots.begin(); it != bots.end(); it++)
        {
            SDL_Texture* texture = TextureFactory::instance(w->getRenderer()).getTexture(
                    filepath + (*it).type.filename);

            Bot* bot = new Bot(w->getRenderer(),
                               texture, (*it).type.frameWidth,
                               (*it).type.frameHeight,
                               (*it).type.numFrames,
                               game,
                               (*it).type.npc,
                               (*it).type.health,
                               (*it).type.collisionDamage);
            PlayerProperty p;
            getBotProperty(*it, p);
            bot->setPhysics(p);
            bot->setFPS((*it).type.fps);

            // detect color
            if ((*it).color.compare("black"))
            {
                bot->setColor(ColorMode::BLACK);
            }
            else if ((*it).color.compare("white"))
            {
                bot->setColor(ColorMode::WHITE);
            }
            else
            {
                bot->setColor(ColorMode::NONE);
            }

            bot->setColorOffset(Vector2f((*it).type.colorOffsetX, (*it).type.colorOffsetY));
            bot->setExplosionSound(filepath + (*it).type.explosionSoundFile);
            bot->setExplosionVolume((*it).type.explosionVolume);
            bot->setScoreValue((*it).type.scorevalue);
            game->addBot(bot);
        }
    }

    void Game::setupGame(string filename, MainWindow* w, Game* game)
    {
        string path = Filesystem::getDirectoryPath(filename);
        XML xml = XML(filename);

        //create Level
        setupLevel(w, game, path + xml.getTileset());

        //create Background layer
        setupBackground(xml.getBackground(), path, w, game);

        //add statusbar
        setupStatusbar(w, game, xml.getStatusbar(), path);

        //add player
        setupPlayer(xml.getPlayer(), w, game, path);

        //setup bots
        setupBots(xml.getLevelBots(), w, game, path);
    }

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

    void Game::addBot(Bot* bot)
    {
        m_bots.push_back(bot);
    }

    void Game::spawnBots()
    {
        int curPos = ((int) m_level->m_camera.x()) + m_level->m_camera.w();

        vector<Bot*> erease_bots;

        for (auto it = m_bots.begin(); it != m_bots.end(); it++)
        {
            if ((*it)->position().x() < curPos + PIXELS_OFFSET_SPAWN_BOTS)
            {
                (*it)->setLiveTime();
                erease_bots.push_back(*it);
                addActor(*it);
            }
        }

        for (auto it = erease_bots.begin(); it != erease_bots.end(); it++)
        {
            auto it1 = std::find(m_bots.begin(), m_bots.end(), *it);
            m_bots.erase(it1);
        }

    }

    Vector2f Game::getPlayerPosition()
    {
        return m_player->position();
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
            m_sound.play(m_volume);

            for (auto it = m_actors.begin(); it != m_actors.end(); ++it)
            {
                (*it)->setHit(false);
            }

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

            removeDeadActors();

            moveActors();

            //added spawn bots
            spawnBots();

            scrollHorizontal();
            checkCameraCollision();
            checkActorCollision();

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
        m_started = true;
    }

    void Game::scrollHorizontal()
    {
        float dt = getElapsedTime();

        Vector2f scrollOffset(m_level->physics().getScrollingSpeed() * dt);
        m_player->setPosition(m_player->position() +
                              m_level->collide(m_player->position(), m_player->w(), m_player->h(), scrollOffset, m_player));
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

    void Game::checkActorCollision()
    {
        CollisionManager cm;

        cm.checkCollision(m_actors);
    }

    void Game::removeDeadActors()
    {
        vector<Actor*> to_remove;

        for (auto it = m_actors.begin(); it != m_actors.end(); ++it)
        {
            if ((*it)->getHealth() <= 0)
            {
                to_remove.push_back(*it);
            }
        }


        for (auto actor : to_remove)
        {
            removeActor(actor);
            if(m_statusBar) {
                if(actor->isKilled() && actor->type() == ActorType::ENEMY)
                {
                    m_statusBar->setScore(m_statusBar->getScore() + actor->getScoreValue());
                }
                if(actor->type() == ActorType::PLAYER || actor->type() == ActorType::ENEMY){
                    actor->playExplosionSound();
                }
            }
            actor->~Actor();
        }
    }

    void Game::setSound(std::string soundFile, int volume){
        m_sound = Sound(soundFile, SoundType::SONG);
        m_volume = volume;
    }
} /* namespace jumper */
