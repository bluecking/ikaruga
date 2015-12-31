/*
 * MainWindow.hpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#ifndef SRC_MAINWINDOW_HPP_
#define SRC_MAINWINDOW_HPP_

#include <string>
#include <SDL.h>

#include "Game.hpp"
#include "WorldProperty.hpp"
namespace jumper
{

class Game;

/***
 *	Represents the main window of the game.
 */
class MainWindow
{
public:

	/***
	 * Creates a main window with given \ref title, width \ref w and height \ref h
	 *
	 * @param title		Title of the window
	 * @param w			Width
	 * @param h			Height
	 */
	MainWindow(std::string title, int w, int h);

	/***
	 * Destructor.
	 */
	~MainWindow();

	/***
	 * Handles user events and renders the current level.
	 */
	void run();

	/***
	 * Gets the current SDL renderer
	 */
	SDL_Renderer* getRenderer();

	void setGame(Game* game);

	/// Returns the window width
	int w();

	/// Retruns the window height
	int h();

private:


	/// Initializes all needed SDL resources
	void initSDL();

	/// Quits SDL and frees all resources
	void quitSDL();

	/// SDL renderer struct
	SDL_Renderer* 		m_renderer;

	/// SDL main window struct
	SDL_Window*			m_window;

	/// Window width
	int					m_width;

	/// Window height
	int					m_height;

	Game*				m_game;

};

} /* namespace jumper */

#endif /* SRC_MAINWINDOW_HPP_ */
