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
		m_levelHeight = m_camera.h() / m_tileHeight;
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
					target.x = (int) floor(j * m_tileWidth - m_camera.x());
					target.y = (int) floor(i * m_tileHeight - m_camera.y() + m_camera.h() % m_tileHeight);

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

void Level::getInnerTiles(Vector2f pos, TilesDirection direction, int width, int height, std::vector<Vector2i>* tiles)
{

	Vector2i posInGrid(floor(pos.x() / m_tileWidth), floor(pos.y() / m_tileHeight));
	Vector2i posInGridEnd(floor((pos.x() - 1 + width) / m_tileWidth), floor((pos.y() - 1 + height) / m_tileHeight));

	if (direction == TUP)
	{
		tiles->push_back(posInGrid);
		tiles->push_back(Vector2i(posInGridEnd.x(), posInGrid.y()));
	}
	else if (direction == TDOWN)
	{
		tiles->push_back(Vector2i(posInGrid.x(), posInGridEnd.y()));
		tiles->push_back(posInGridEnd);
	}
	else if (direction == TLEFT)
	{
		tiles->push_back(posInGrid);
		tiles->push_back(Vector2i(posInGrid.x(), posInGridEnd.y()));
	}
	else if (direction == TRIGHT)
	{
		tiles->push_back(Vector2i(posInGridEnd.x(), posInGrid.y()));
		tiles->push_back(posInGridEnd);
	}

	return;
}

void Level::getSurroundingRelevantTiles(Vector2f pos, TilesDirection direction, int width, int height, std::vector<Vector2i>* tiles)
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


float Level::nextEdge(float playerPos, int playerSize, int tileGridPos, int edgeBonus)
{
	return ((tileGridPos + edgeBonus) * m_tileWidth) - (playerPos + playerSize);
}

float Level::posRelativToGrid(float pos, int grid)
{
	return pos - grid * m_tileWidth;
}

float Level::gridToPos(int grid)
{
	return grid * m_tileWidth;
}

int Level::posToGrid(float pos)
{
	return floor(pos / m_tileWidth);
}

	Vector2f Level::collide(Vector2f pos, int width, int height, Vector2f move, Actor* actor)
	{
		pos -= Vector2f(0, m_camera.h() % m_tileHeight);

		return collideRC(pos, width, height, move, actor);
	}

Vector2f Level::collideRC(Vector2f pos, int width, int height, Vector2f move, Actor* actor)
{
	pos.setY(pos.y() < 0 ? 0 : pos.y());
	pos.setY(pos.y() + height > m_levelHeight * m_tileHeight ? m_levelHeight * m_tileHeight - height : pos.y());

	bool checkY = true;

	move = collideX(pos, width, height, move, actor, checkY);

	pos += Vector2f(move.x(), 0);

	if (checkY)
	{
		move = collideY(pos, width, height, move, actor);
	}

	return move;
}


	Vector2f Level::collideX(Vector2f pos, int width, int height, Vector2f move, Actor* actor, bool& checkY)
	{
		float x = move.x();
		float y = move.y();

		std::vector<Vector2i> tiles;

		if (x != 0)
		{
			if (x > 0)
			{
				getInnerTiles(pos, TRIGHT, width, height, &tiles);

				TileType t1 = m_tileTypes[(m_tiles[tiles[0].y()])[tiles[0].x()]];
				TileType t2 = m_tileTypes[(m_tiles[tiles[1].y()])[tiles[1].x()]];

				if (t1 != EDGETOPRIGHT && t2 != EDGEDOWNRIGHT) // right movement no slope collision
				{

					tiles.clear();

					getSurroundingRelevantTiles(pos, TRIGHT, width, height, &tiles);

					int round = 0;

					for(Vector2i& tPos : tiles)
					{

						if (tPos.x() < m_levelWidth && tPos.y() < m_levelHeight && tPos.x() >= 0 && tPos.y() >= 0) // movement out of map boundary
						{
							TileType t = m_tileTypes[(m_tiles[tPos.y()])[tPos.x()]];

							if ((t != NONSOLID && (round != 0 && round != tiles.size() - 1)) || (round == 0 && (t != EDGETOPRIGHT) && t != NONSOLID) || (round == tiles.size() - 1 && (t != EDGEDOWNRIGHT && t != NONSOLID))) // collide with something solid
							{
								float maxMov = (tPos.x() * m_tileWidth) - (pos.x() + width);
								x = std::min(x, maxMov);

								if (x == maxMov)
								{
									actor->onCollide();
								}

								break;
							}
						}

						round++;
					}

					TileType t1 = m_tileTypes[(m_tiles[tiles[0].y()])[tiles[0].x()]];
					TileType t2 = m_tileTypes[(m_tiles[tiles[tiles.size() - 1].y()])[tiles[tiles.size() - 1].x()]];

					if (t1 == EDGETOPRIGHT && t2 == EDGEDOWNRIGHT) // next tile is slope movement (there is a chance some of the cases aren't needed)
					{
						if (tiles.size() * m_tileHeight >= height + 2) // you can move into the edge
						{
							int tHeight = height - (tiles.size() - 2) * m_tileHeight;
							tHeight /= 2;

							float maxMov = m_tileHeight - tHeight;

							if (0 < x - ((tiles[0].x() * m_tileWidth) - pos.x() - width)) // you move into the edge
							{
								x = std::min(x - ((tiles[0].x() * m_tileWidth) - pos.x() - width), maxMov);

								int upY = tiles[0].y() * m_tileHeight;
								int downY = (tiles[tiles.size() - 1].y() + 1) * m_tileHeight;

								int pUp = pos.y();
								int pDown = pos.y() + height;

								if (pUp - upY <= downY - pDown)
								{
									if (pos.y() + y < upY + x)
									{
										y = x + upY - pos.y();
									}
								}
								else
								{
									if (pos.y() + y + height > downY - x)
									{
										y = downY - x - pos.y() - height;
									}
								}

								x += ((tiles[0].x() * m_tileWidth) - pos.x() - width);

								checkY = false;

							}
						}
						else // you can't move into the edge
						{
							float maxMov = (tiles[0].x() * m_tileWidth) - (pos.x() + width);
							x = std::min(x, maxMov);
						}

						// TODO
					}
					else if (t1 == EDGETOPRIGHT) // next tile is slope movement (there is a chance some of the cases aren't needed)
					{
						// TODO
					}
					else if (t2 == EDGEDOWNRIGHT) // next tile is slope movement (there is a chance some of the cases aren't needed)
					{
						// TODO
					}
				}
				else if (t2 != EDGEDOWNRIGHT) // t1 == EDGETOPRIGHT no collision down check, slope collision right
				{
					checkY = false;

					float maxMovEdge = nextEdge(pos.x(), width, tiles[0].x(), 1);

					float movRec = x - maxMovEdge;

					x = std::min(x, maxMovEdge);

					int upY = gridToPos(tiles[0].y());

					if (pos.y() + y < upY + posRelativToGrid(pos.x() + width + x, tiles[0].x()) + 1) // check if we would collide in next step
					{
						y = upY + posRelativToGrid(pos.x() + width + x, tiles[0].x()) - pos.y() + 1; // stop before you are stuck in edge

						actor->onCollide();
					}

					float y2 = collideY(Vector2f(pos.x() + x, pos.y()), width, height, Vector2f(0, y), actor).y(); // repeation

					x -= y - y2;
					y = y2;

					if (movRec > 0 && posToGrid(pos.y() + y) != tiles[0].y())
					{
						Vector2f newMov = collideRC(Vector2f(pos.x() + x, pos.y() + y), width, height, Vector2f(movRec, 0), actor);

						x += newMov.x();
						y += newMov.y();
					}
				}
				else if (t1 != EDGETOPRIGHT) // t2 == EDGEDOWNRIGHT, slope collision right
				{
					checkY = false;

					float maxMovEdge = nextEdge(pos.x(), width, tiles[1].x(), 1);

					float movRec = x - maxMovEdge;

					x = std::min(x, maxMovEdge);

					int downY = gridToPos(tiles[1].y() + 1);

					if (pos.y() + y + height > downY - (posRelativToGrid(pos.x() + width + x, tiles[1].x()) + 1)) // check if we would collide in next step
					{
						y = downY - (posRelativToGrid(pos.x() + width + x, tiles[1].x()) + 1) - (pos.y() + height); // stop before you are stuck in edge

						actor->onCollide();
					}

					float y2 = collideY(Vector2f(pos.x() + x, pos.y()), width, height, Vector2f(0, y), actor).y(); // repeation

					x -= y2 - y;
					y = y2;

					if (movRec > 0 && posToGrid(pos.y() + y + height) != tiles[1].y())
					{
						Vector2f newMov = collideRC(Vector2f(pos.x() + x, pos.y() + y), width, height, Vector2f(movRec, 0), actor);

						x += newMov.x();
						y += newMov.y();
					}
				}
				else // t1 and t2 EDGEs, slope collision right
				{
					// TODO
				}
			}
			else
			{
				getInnerTiles(pos, TLEFT, width, height, &tiles);

				TileType t1 = m_tileTypes[(m_tiles[tiles[0].y()])[tiles[0].x()]];
				TileType t2 = m_tileTypes[(m_tiles[tiles[1].y()])[tiles[1].x()]];

				if (t1 != EDGETOPLEFT && t2 != EDGEDOWNLEFT)
				{

					tiles.clear();

					getSurroundingRelevantTiles(pos, TLEFT, width, height, &tiles);

					int round = 0;

					for(Vector2i& tPos : tiles)
					{
						if (tPos.x() < m_levelWidth && tPos.y() < m_levelHeight && tPos.x() >= 0 && tPos.y() >= 0)
						{
							TileType t = m_tileTypes[(m_tiles[tPos.y()])[tPos.x()]];

							if ((t != NONSOLID && (round != 0 && round != tiles.size() - 1)) || (round == 0 && (t != EDGETOPLEFT && t != NONSOLID)) || (round == tiles.size() - 1 && (t != EDGEDOWNLEFT && t != NONSOLID))) // collide with something solid
							{
								float maxMov = (tPos.x() * m_tileWidth + m_tileWidth) - (pos.x());
								x = std::max(x, maxMov);

								if (x == maxMov)
								{
									actor->onCollide();
								}

								break;
							}
						}

						round++;
					}

					TileType t1 = m_tileTypes[(m_tiles[tiles[0].y()])[tiles[0].x()]];
					TileType t2 = m_tileTypes[(m_tiles[tiles[tiles.size() - 1].y()])[tiles[tiles.size() - 1].x()]];

					if (t1 == EDGETOPLEFT && t2 == EDGEDOWNLEFT) // next tile is slope movement (there is a chance some of the cases aren't needed
					{
						// TODO
					}
					else if (t1 == EDGETOPLEFT) // next tile is slope movement (there is a chance some of the cases aren't needed
					{
						// TODO
					}
					else if (t2 == EDGEDOWNLEFT) // next tile is slope movement (there is a chance some of the cases aren't needed
					{
						// TODO
					}
				}
				else if (t2 != EDGEDOWNLEFT) // t1 == EDGETOPLEFT no collision down check, slope collision left
				{
					checkY = false;

					float maxMovEdge = nextEdge(pos.x(), 0, tiles[0].x(), 0);

					float movRec = x - maxMovEdge;

					x = std::max(x, maxMovEdge);

					int upY = gridToPos(tiles[0].y());

					if (pos.y() + y < upY + m_tileWidth - posRelativToGrid(pos.x() + x, tiles[0].x()) + 1) // check if we would collide in next step
					{
						y = upY + m_tileWidth - posRelativToGrid(pos.x() + x, tiles[0].x()) - pos.y() + 1; // stop before you are stuck in edge

						actor->onCollide();
					}

					float y2 = collideY(Vector2f(pos.x() + x, pos.y()), width, height, Vector2f(0, y), actor).y(); // repeation

					x += y - y2;
					y = y2;

					if (movRec < 0 && posToGrid(pos.y() + y) != tiles[0].y())
					{
						Vector2f newMov = collideRC(Vector2f(pos.x() + x, pos.y() + y), width, height, Vector2f(movRec, 0), actor);

						x += newMov.x();
						y += newMov.y();
					}
				}
				else if (t1 != EDGETOPLEFT) // t2 == EDGEDOWNLEFT, slope collision left
				{
					checkY = false;

					float maxMovEdge = nextEdge(pos.x(), 0, tiles[1].x(), 0);

					float movRec = x - maxMovEdge;

					x = std::max(x, maxMovEdge);

					int downY = gridToPos(tiles[1].y() + 1);

					if (pos.y() + y + height > downY - (m_tileWidth - posRelativToGrid(pos.x() + x, tiles[1].x()) + 1)) // check if we would collide in next step
					{
						y = downY - (m_tileWidth - posRelativToGrid(pos.x() + x, tiles[1].x()) + 1) - (pos.y() + height); // stop before you are stuck in edge

						actor->onCollide();
					}

					float y2 = collideY(Vector2f(pos.x() + x, pos.y()), width, height, Vector2f(0, y), actor).y(); // repeation

					x += y2 - y;
					y = y2;

					if (movRec < 0 && posToGrid(pos.y() + y + height) != tiles[1].y())
					{
						Vector2f newMov = collideRC(Vector2f(pos.x() + x, pos.y() + y), width, height, Vector2f(movRec, 0), actor);

						x += newMov.x();
						y += newMov.y();
					}
				}
				else // t1 and t2 EDGEs, slope collision left
				{
					// TODO
				}
			}
		}

		return Vector2f(x, y);
	}

Vector2f Level::collideY(Vector2f pos, int width, int height, Vector2f move, Actor* actor)
{
	float x = move.x();
	float y = move.y();

	std::vector<Vector2i> tiles;

	if (y != 0)
	{
		if (y> 0)
		{
			getInnerTiles(pos, TDOWN, width, height, &tiles);

			TileType t1 = m_tileTypes[(m_tiles[tiles[0].y()])[tiles[0].x()]];
			TileType t2 = m_tileTypes[(m_tiles[tiles[1].y()])[tiles[1].x()]];

			if (t1 != EDGEDOWNLEFT && t2 != EDGEDOWNRIGHT) // right movement no slope collision
			{
				tiles.clear();

				getSurroundingRelevantTiles(pos, TDOWN, width, height, &tiles);

				int round = 0;

				for (Vector2i &tPos : tiles)
				{
					if (tPos.x() < m_levelWidth && tPos.y() < m_levelHeight && tPos.x() >= 0 && tPos.y() >= 0)
					{
						TileType t = m_tileTypes[(m_tiles[tPos.y()])[tPos.x()]];

						if ((t != NONSOLID && (round != 0 && round != tiles.size() - 1)) || (round == 0 && (t != EDGEDOWNLEFT && t != NONSOLID)) || (round == tiles.size() - 1 && (t != EDGEDOWNRIGHT && t != NONSOLID)))
						{
							float maxMov = (tPos.y() * m_tileHeight) - (pos.y() + height);
							y = std::min(y, maxMov);

							if (y == maxMov)
							{
								actor->onCollide();
							}

							break;
						}
					}

					round++;
				}

				TileType t1 = m_tileTypes[(m_tiles[tiles[0].y()])[tiles[0].x()]];
				TileType t2 = m_tileTypes[(m_tiles[tiles[tiles.size() - 1].y()])[tiles[tiles.size() - 1].x()]];

				if (t1 == EDGEDOWNLEFT && t2 == EDGEDOWNRIGHT) // next tile is slope movement (there is a chance some of the cases aren't needed)
				{
					// TODO
				}
				else if (t1 == EDGEDOWNLEFT) // next tile is slope movement (there is a chance some of the cases aren't needed)
				{
					// TODO
				}
				else if (t2 == EDGEDOWNRIGHT) // next tile is slope movement (there is a chance some of the cases aren't needed)
				{
					// TODO
				}
			}
			else if (t2 != EDGEDOWNRIGHT) // t1 == EDGEDOWNLEFT no collision down check, slope collision right
			{
				float downY = gridToPos(tiles[0].y() + 1);

				if (pos.y() + y + height > downY - (m_tileHeight - posRelativToGrid(pos.x(), tiles[0].x())) + 1)
				{
					y = (downY - (m_tileHeight - posRelativToGrid(pos.x(), tiles[0].x())) + 1) - (pos.y() + height);
				}
			}
			else if (t1 != EDGEDOWNLEFT) // t2 == EDGEDOWNRIGHT, slope collision right
			{
				float downY = gridToPos(tiles[0].y() + 1);

				if (pos.y() + y + height > downY - (posRelativToGrid(pos.x(), tiles[0].x())) + 1)
				{
					y = (downY - (posRelativToGrid(pos.x(), tiles[0].x())) + 1) - (pos.y() + height);
				}
			}
			else // t1 and t2 EDGEs, slope collision right
			{
				// TODO
			}
		}
		else
		{
			getInnerTiles(pos, TUP, width, height, &tiles);

			TileType t1 = m_tileTypes[(m_tiles[tiles[0].y()])[tiles[0].x()]];
			TileType t2 = m_tileTypes[(m_tiles[tiles[1].y()])[tiles[1].x()]];

			if (t1 != EDGETOPLEFT && t2 != EDGETOPRIGHT) // right movement no slope collision
			{

				tiles.clear();

				getSurroundingRelevantTiles(pos, TUP, width, height, &tiles);

				int round = 0;

				for (Vector2i &tPos : tiles)
				{
					if (tPos.x() < m_levelWidth && tPos.y() < m_levelHeight && tPos.x() >= 0 && tPos.y() >= 0)
					{
                        TileType t = m_tileTypes[(m_tiles[tPos.y()])[tPos.x()]];

                        if ((t != NONSOLID && (round != 0 && round != tiles.size() - 1)) || (round == 0 && (t != EDGETOPLEFT) && t != NONSOLID) || (round == tiles.size() - 1 && (t != EDGETOPRIGHT && t != NONSOLID))) // collide with something solid
                        {
							float maxMov = (tPos.y() * m_tileHeight + m_tileHeight) - (pos.y());
							y = std::max(y, maxMov);

							if (y == maxMov)
							{
								actor->onCollide();
							}

							break;
						}
					}

					round++;
				}

                TileType t1 = m_tileTypes[(m_tiles[tiles[0].y()])[tiles[0].x()]];
                TileType t2 = m_tileTypes[(m_tiles[tiles[tiles.size() - 1].y()])[tiles[tiles.size() - 1].x()]];

                if (t1 == EDGETOPLEFT && t2 == EDGETOPRIGHT) // next tile is slope movement (there is a chance some of the cases aren't needed
                {
                    // TODO
                }
                else if (t1 == EDGETOPLEFT) // next tile is slope movement (there is a chance some of the cases aren't needed
                {
                    // TODO
                }
                else if (t2 == EDGETOPRIGHT) // next tile is slope movement (there is a chance some of the cases aren't needed
                {
                    // TODO
                }
			}
			else if (t2 != EDGETOPRIGHT) // t1 == EDGETOPLEFT no collision down check, slope collision left
			{
				float downY = gridToPos(tiles[0].y() + 1);

				if(pos.y() + y < downY - posRelativToGrid(pos.x(), tiles[0].x()) + 1)
				{
					y = (downY - posRelativToGrid(pos.x(), tiles[0].x()) + 1) - pos.y();
				}
			}
			else if (t1 != EDGETOPLEFT) // t2 == EDGETOPRIGHT, slope collision left
			{
				float upY = gridToPos(tiles[1].y());

				if(pos.y() + y < upY + posRelativToGrid(pos.x() + width, tiles[1].x()) + 1)
				{
					y = (upY + posRelativToGrid(pos.x() + width, tiles[1].x()) + 1) - pos.y();
				}
			}
			else // t1 and t2 EDGEs, slope collision left
			{
				// TODO
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

