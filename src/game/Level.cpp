/*
 * Level.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "Actor.hpp"
#include "Level.hpp"
#include "StaticRenderable.hpp"

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
using std::cout;
using std::endl;

#include <SDL_image.h>


namespace jumper
{


Level::Level(SDL_Renderer* renderer, std::string filename) : StaticRenderable(renderer)
{
	// Set all default values
	m_texture 		= 0;
	m_tileWidth 	= 0;
	m_tileHeight	= 0;
	m_tileOffset 	= 0;
	m_numRows = 0;
	m_tilesPerRow = 0;
	m_levelWidth = 0;
	m_levelHeight = 0;

	// Read meta data from level file
	std::ifstream in(filename.c_str());
	std::string texFileName;

	if(in.good())
	{
		in >> texFileName;
		in >> m_tileWidth >> m_tileHeight >> m_tilesPerRow >> m_numRows;
		in >> m_tileOffset;
		in >> m_levelWidth;
		m_levelHeight = 576 / m_tileHeight;
	}
	else
	{
		std::cout << "Unable to open file " << filename << std::endl;
	}

	SparseMatrix tiles(m_levelHeight, m_levelWidth);
	m_tiles = tiles;

	// Load texture
	std::size_t found = filename.find_last_of("/\\");
	string path = filename.substr(0,found);

	m_texture = TextureFactory::instance(m_renderer).getTexture(path + "/" + texFileName);

	if(!m_texture)
	{
		std::cout << "Unable to load texture " << texFileName << std::endl;
	}

	// Read tile indices
	for(int i = 0; i < m_levelHeight; i++)
	{
		for(int j = 0; j < m_levelWidth; j++)
		{
			int tileID;
			in >> tileID;
			m_tiles.insert(i, j, tileID);
		}
	}

	in.close();

	string texFileTileInfo = texFileName.substr(0, texFileName.find_last_of("."));

	texFileTileInfo += ".ti";

	texFileTileInfo = path + "/" + texFileTileInfo;
	
	std::ifstream inTileInfo(texFileTileInfo.c_str());

	m_tileTypes.push_back(NONSOLID); // for id=0

	if (inTileInfo.good())
	{

	for(int i = 0; i < m_numRows; i++)
	{
		for(int j = 0; j < m_tilesPerRow; j++)
		{

			int tileType = 0;

			inTileInfo >> tileType;

			m_tileTypes.push_back((TileType) tileType);

		}

	}
		



	}
	else
	{
		std::cout << "Unable to open file " << texFileTileInfo << std::endl;
	}

	inTileInfo.close();

}


void Level::render()
{
	if(getRenderer() && m_texture)
	{

		int i;
		int j;
		int tile_index;
		int col, row;
		SDL_Rect target;
		SDL_Rect source;


		target.w = m_tileWidth;
		target.h = m_tileHeight;

		source.w = m_tileWidth;
		source.h = m_tileHeight;


		for(i = 0; i < m_levelHeight; i++)
		{
			for(j = 0; j < m_levelWidth; j++)
			{
				tile_index = m_tiles[i][j] - 1;
				if(tile_index >= 0)
				{
					//Compute the position of the target on the screen
					target.x = j * m_tileWidth - m_camera.x();
					target.y = i * m_tileHeight - m_camera.y() + 576 % m_tileHeight;

					// Don't render tiles outside the frustrum. To prevent popping,
					// add some extra margin
					if(target.x + target.h > -m_tileWidth && target.x + target.h < m_camera.w() + m_tileWidth)
					{

						row = tile_index / m_tilesPerRow;
						col = tile_index % m_tilesPerRow;

						source.x = col * m_tileWidth;
						if(col > 0)
						{
							source.x += col * m_tileOffset;
						}

						source.y = row * m_tileHeight;
						if(row > 0)
						{
							source.y += row * m_tileOffset;
						}

						// Copy pixel date to correct position
						SDL_RenderCopy(getRenderer(), m_texture, &source, &target);
					}
				}
			}
		}
	}
}

WorldProperty& Level::physics()
{
	return m_levelPhysics;
}

void Level::getSurroundingTiles(Vector2f pos, int width, int height, Vector2i *tiles)
{
    /* Determine x and y position of the sprite within the grid */
    Vector2i gridPos(floor((pos.x() + 0.5 * width) / m_tileWidth), floor((pos.y() + 0.5 * height) / m_tileHeight));

    /* Get the surrounding tiles in "priority" order, i.e., we want
     * check some collisions like left before we check the others
     */
    tiles[0].setX(gridPos.x() - 1);
    tiles[0].setY(gridPos.y() - 1);

    tiles[1].setX(gridPos.x());
    tiles[1].setY(gridPos.y() - 1);

    tiles[2].setX(gridPos.x() + 1);
    tiles[2].setY(gridPos.y() - 1);

    tiles[3].setX(gridPos.x() - 1);
    tiles[3].setY(gridPos.y());

    tiles[4].setX(gridPos.x() + 1);
    tiles[4].setY(gridPos.y());

    tiles[5].setX(gridPos.x() - 1);
    tiles[5].setY(gridPos.y() + 1);

    tiles[6].setX(gridPos.x());
    tiles[6].setY(gridPos.y() + 1);

    tiles[7].setX(gridPos.x() + 1);
    tiles[7].setY(gridPos.y() + 1);


}

void Level::getSurroundingRelevantTiles(Vector2f pos, TilesDirection direction, int width, int height, std::vector<Vector2i> *tiles)
{

	Vector2i posInGrid(floor(pos.x() / m_tileWidth), floor(pos.y() / m_tileHeight));
	Vector2i posInGridEnd(floor((pos.x() - 1 + width) / m_tileWidth), floor((pos.y() - 1 + height) / m_tileHeight));

	int sizeX = posInGridEnd.x() - posInGrid.x() + 1;
	int sizeY = posInGridEnd.y() - posInGrid.y() + 1;

	Vector2i tile;

	if (direction == TUP)
	{

		posInGrid -= Vector2i(0, 1);

		for (int x = 0; x < sizeX; x++)
		{

			tile.setX(posInGrid.x() + x);
			tile.setY(posInGrid.y());

			tiles->push_back(tile);

		}

	}
	else if (direction == TDOWN)
	{

		posInGrid += Vector2i(0, sizeY);

		for (int x = 0; x < sizeX; x++)
		{

			tile.setX(posInGrid.x() + x);
			tile.setY(posInGrid.y());

			tiles->push_back(tile);

		}

	}
	else if (direction == TLEFT)
	{

		posInGrid -= Vector2i(1, 0);

		for (int y = 0; y < sizeY; y++)
		{

			tile.setX(posInGrid.x());
			tile.setY(posInGrid.y() + y);

			tiles->push_back(tile);

		}

	}
	else if (direction == TRIGHT)
	{

		posInGrid += Vector2i(sizeX, 0);

		for (int y = 0; y < sizeY; y++)
		{

			tile.setX(posInGrid.x());
			tile.setY(posInGrid.y() + y);

			tiles->push_back(tile);

		}

	}

	

}


Vector2f Level::collide(Vector2f pos, int width, int height, Vector2f move)
{

	pos -= Vector2f(0,  576 % m_tileHeight);

	float x = move.x();
	float y = move.y();

	std::vector<Vector2i> tiles;

	if (x != 0)
	{

		if (x > 0)
		{

			getSurroundingRelevantTiles(pos, TRIGHT, width, height, &tiles);

			for(Vector2i& tPos : tiles)
			{

				if (tPos.x() < m_levelWidth && tPos.y() < m_levelHeight && tPos.x() >= 0 && tPos.y() >= 0)
				{

					if (m_tileTypes[(m_tiles[tPos.y()])[tPos.x()]] == SOLID)
					{

						float maxMov = (tPos.x() * m_tileWidth) - (pos.x() + width);

						x = std::min(x, maxMov);

						break;

					}

				}

			}

		}
		else
		{

			getSurroundingRelevantTiles(pos, TLEFT, width, height, &tiles);

			for(Vector2i& tPos : tiles)
			{

				if (tPos.x() < m_levelWidth && tPos.y() < m_levelHeight && tPos.x() >= 0 && tPos.y() >= 0)
				{

					if (m_tileTypes[m_tiles[tPos.y()][tPos.x()]] == SOLID)
					{

						float maxMov = (tPos.x() * m_tileWidth + m_tileWidth) - (pos.x());

						x = std::max(x, maxMov);

						break;

					}

				}

			}

		}

	}


	tiles.clear();
	pos += Vector2f(x, 0);


	if (y != 0)
	{

		if (y> 0)
		{

			getSurroundingRelevantTiles(pos, TDOWN, width, height, &tiles);

			for(Vector2i& tPos : tiles)
			{

				if (tPos.x() < m_levelWidth && tPos.y() < m_levelHeight && tPos.x() >= 0 && tPos.y() >= 0)
				{

					if (m_tileTypes[m_tiles[tPos.y()][tPos.x()]] == SOLID)
					{

						float maxMov = (tPos.y() * m_tileHeight) - (pos.y() + height);

						y = std::min(y, maxMov);

						break;

					}

				}

			}

		}
		else
		{

			getSurroundingRelevantTiles(pos, TUP, width, height, &tiles);

			for(Vector2i& tPos : tiles)
			{

				if (tPos.x() < m_levelWidth && tPos.y() < m_levelHeight && tPos.x() >= 0 && tPos.y() >= 0)
				{

					if (m_tileTypes[m_tiles[tPos.y()][tPos.x()]] == SOLID)
					{

						float maxMov = (tPos.y() * m_tileHeight + m_tileHeight) - (pos.y());

						y = std::max(y, maxMov);

						break;

					}

				}

			}

		}

	}


	return Vector2f(x, y);

}


int Level::levelHeight() const
{
    return m_levelHeight;
}

int Level::levelWidth() const
{
    return m_levelWidth;
}

SparseMatrix& Level::tiles()
{
    return m_tiles;
}

int Level::tileWidth() const
{
    return m_tileWidth;
}

int Level::tileHeight() const
{
    return m_tileHeight;
}

Level::~Level()
{
    // Free texture resources
    SDL_DestroyTexture(m_texture);
}

Collision Level::resolveCollision(Actor* player)
{
	SDL_Rect tileRect;
	SDL_Rect spriteRect;
	SDL_Rect intersectionRect;
	Vector2f desiredPosition;
	Vector2i surroundingTiles[8];
	int n, i ,j;

	int dx = 0;
	int dy = 0;

	// Set desired position to new position
	desiredPosition = player->position();

	// Check if sprite intersects with one of its surrounding tiles
	getSurroundingTiles(desiredPosition, player->w(), player->h(), surroundingTiles);
	int d_i, d_j;
	int f_i, f_j;
	f_i = surroundingTiles[6].y();
	f_j = surroundingTiles[6].x();

	if(player->physics().velocity().x() > 0)
	{
		d_i = surroundingTiles[7].y();
		d_j = surroundingTiles[7].x();
	}
	else
	{
		d_i = surroundingTiles[5].y();
		d_j = surroundingTiles[5].x();
	}

	for(n = 0; n < 8; n++)
	{
		j = surroundingTiles[n].x();
		i = surroundingTiles[n].y();

		// Check, if tile coordinates are valid
		if((i >= 0) && (i < m_levelHeight) && (j >= 0) && (j < m_levelWidth) )
		{
			if(m_tiles[i][j] > 0)
			{
				// Get SDL rect for current tile and sprite and check intersection
				tileRect.y = i * m_tileHeight;
				tileRect.x = j * m_tileWidth;
				tileRect.w = m_tileWidth;
				tileRect.h = m_tileHeight;

				spriteRect.x = desiredPosition.x();
				spriteRect.y = desiredPosition.y();
				spriteRect.w = player->w();
				spriteRect.h = player->h();

				if(SDL_IntersectRect(&tileRect, &spriteRect, &intersectionRect))
				{
					if(n == 3)
					{
						dx = 100;
					}

					// Handle pose correction cases
					if(n == 4)
					{
						dx = 100;
						desiredPosition.setX(desiredPosition.x() - intersectionRect.w);
					}
					else if(n == 1)
					{
						desiredPosition.setY(desiredPosition.y() + intersectionRect.h);
					}
					else if(n == 3)
					{
						desiredPosition.setX(desiredPosition.x() + intersectionRect.w);
					}
					else if(n == 6)
					{
						desiredPosition.setY(desiredPosition.y() - intersectionRect.h);
					}
					else
					{
						if(intersectionRect.w >= 2 && intersectionRect.h >= 2)
						{
							if(intersectionRect.w > intersectionRect.h)
							{
								if( (n == 5) || (n == 7))
								{
									desiredPosition.setY(desiredPosition.y() - intersectionRect.h);
								}
								else
								{
									desiredPosition.setY(desiredPosition.y() + intersectionRect.h);
								}
							}
							else
							{
								if( (n == 2) || (n == 7))
								{
									desiredPosition.setX(desiredPosition.x() - intersectionRect.w);
								}
								else
								{
									desiredPosition.setX(desiredPosition.x() + intersectionRect.w);
								}
							}
						}
					}
				}
			}
		}
	}



	player->setPosition(Vector2f(desiredPosition.x(), desiredPosition.y()));

	return Collision(Vector2i(dx, dy));
}


} /* namespace jumper */

