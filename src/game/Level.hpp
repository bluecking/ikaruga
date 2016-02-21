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
#include "Vector.hpp"
#include "WorldProperty.hpp"
#include "Collision.hpp"
#include "TextureFactory.hpp"


namespace jumper
{


class Actor;

/**
 * @brief Represents a level in the jumper game.
 */
class Level : public StaticRenderable
{
public:

	/**
	 * Loads a level from the given .lvl file
	 *
	 * @param filename
	 */
	Level(SDL_Renderer* renderer, std::string filename);

	/**
	 * Renders the level to the given renderer
	 *
	 * @param renderer		A SDL_Renderer to render the tiles
	 */
	virtual void render();

	/// Returns the number of tiles in a row
	int levelHeight() const;

	/// Returns the number of tile rows
	int levelWidth() const;

	/// Returns the tile width
	int tileWidth() const;

	/// Returns the tile height
	int tileHeight() const;

	/// Returns the matrix of tiles
	SparseMatrix& tiles();

	/// Returns the physical properties of the level
	WorldProperty& physics();

	/**
	 * Destructor
	 */
	virtual ~Level();

	/// Generates a collision object between the level and the actor
	Collision resolveCollision(Actor* actor);

private:

	/// Returns the surrounding tiles of the given position
	void getSurroundingTiles(Vector2f pos, int width, int height, Vector2i *tiles);


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

	/// Tile matrix
	SparseMatrix		m_tiles;
};

} /* namespace jumper */

#endif /* SRC_LEVEL_HPP_ */