/*
 * Game.hpp
 *
 *  Created on: Dec 11, 2015
 *      Author: twiemann
 */

#ifndef SRC_GAME_HPP_
#define SRC_GAME_HPP_

#include "MainWindow.hpp"
#include "Actor.hpp"
#include "Bot.hpp"
#include "Player.hpp"
#include "Level.hpp"

#include <vector>
using std::vector;

namespace jumper
{

class MainWindow;

/*
 *
 */
class Game
{
public:

	/// Constructor
	Game(MainWindow* window);

	/// Destructor
	virtual ~Game();

	/// Sets the player object
	void setPlayer(Player* player);

	/// Sets the current level
	void setLevel(Level* level);

	/// Adds a new bot to the scene
	void addBot(Bot* bot);

	/// Updates the current state according to the given key states
	void update(const Uint8* &currentKeyStates);

	void start();

private:

	void updateCameraPosition();

	/// All renderables in the game
	vector<Renderable*> 	m_renderables;

	/// All actors
	vector<Actor*>			m_actors;

	/// The user controlled player
	Player*					m_player;

	/// The current level
	Level*					m_level;

	/// Pointer to the main window of the game
	SDL_Renderer*			m_renderer;

	/// Window width
	int						m_windowWidth;

	/// Window height
	int						m_windowHeight;
};

} /* namespace jumper */

#endif /* SRC_GAME_HPP_ */
