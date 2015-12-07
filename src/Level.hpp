/*
 * Level.hpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#ifndef SRC_LEVEL_HPP_
#define SRC_LEVEL_HPP_

#include <string>
#include <SDL.h>

#include "Camera.hpp"
#include "StaticRenderable.hpp"
#include "SparseMatrix.hpp"
#include "Player.hpp"
#include "Vector.hpp"
#include "WorldProperty.hpp"

namespace jumper
{

/***
 * Represents a level in the jumper game.
 */
class Level : public StaticRenderable
{
public:

	/***
	 * Loads a level from the given file
	 *
	 * @param filename
	 */
	Level(SDL_Renderer* renderer, std::string filename, Camera & cam);

	/***
	 * Renders the level to the given renderer
	 *
	 * @param renderer		A SDL_Renderer to render the tiles
	 */
	virtual void render();

	int levelHeight() const;

	int levelWidth() const;

	int tileWidth() const;

	int tileHeight() const;

	SparseMatrix& tiles();

	WorldProperty getPhysics() const;
	/***
	 * Destructor
	 */
	virtual ~Level();

	void setPlayer(Player* player);

	void checkAndResolveCollision();

	void updatePlayerPosition(int move, bool jump, double dt);

private:

	void getSurroundingTiles(Vector2f pos, int width, int height, Camera &cam, Vector2i *tiles);


	/// Tile width
	int					m_tileWidth;

	/// Tile height
	int					m_tileHeight;

	/// Offset between the tiles in the tile sheet
	int					m_tileOffset;

	/// Number of rows in the tile sheet
	int 				m_numRows;

	/// Key color red component
	unsigned char	 	m_keyR;

	/// Key color green component
	unsigned char		m_keyG;

	/// Key color blue component
	unsigned char		m_keyB;

	/// Number of tiles per row
	int					m_tilesPerRow;

	/// Level width
	int					m_levelWidth;

	/// Level height
	int					m_levelHeight;

	///Physical properties of level
	WorldProperty		m_levelPhysics;

	Camera  			m_camera;

	SparseMatrix		m_tiles;

	Player*				m_player;

};

} /* namespace jumper */

#endif /* SRC_LEVEL_HPP_ */
