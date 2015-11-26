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
#include "Renderable.hpp"
#include "Vector2F.hpp"

namespace jumper
{

/***
 * Represents a level in the jumper game.
 */
class Level : Renderable
{
public:
	/***
	 * Loads a level from the given file
	 *
	 * @param filename
	 */
	Level(SDL_Renderer* renderer, std::string filename);

	/***
	 * Renders the level to the given renderer
	 *
	 * @param renderer		A SDL_Renderer to render the tiles
	 */
	void render(Camera& cam);

	void getSurroundingTiles(Vector2F pos, int width, int height, Camera &cam, Pixel tiles[]);

	int getM_levelHeight() const;

	int getM_levelWidth() const;

	int getM_tileWidth() const;

	int getM_tileHeight() const;

	int** getM_tiles() const;
	/***
	 * Destructor
	 */
	~Level();




private:

	typedef Pixel Vector2I;

	/// A SDL texture for the tile sheet
	SDL_Texture*		m_texture;

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

	/// Array for tile definitions
	int**				m_tiles;


};

} /* namespace jumper */

#endif /* SRC_LEVEL_HPP_ */
