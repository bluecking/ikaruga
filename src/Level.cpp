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
#include <SDL_image.h>


namespace jumper
{


Level::Level(SDL_Renderer* renderer, std::string filename, Camera & camera) : StaticRenderable(renderer), m_camera(camera)
{
	// Set all default values
	m_texture 		= 0;
	m_tileWidth 	= 0;
	m_tileHeight	= 0;
	m_tileOffset 	= 0;
	m_numRows = 0;
	m_keyR = 0;
	m_keyG = 0;
	m_keyB = 0;
	m_tilesPerRow = 0;
	m_levelWidth = 0;
	m_levelHeight = 0;

	// Read meta data from level file
	std::ifstream in(filename.c_str());
	std::string texFileName;

	int ir, ig, ib;

	if(in.good())
	{
		in >> texFileName;
		in >> m_tileWidth >> m_tileHeight >> m_tilesPerRow >> m_numRows;
		in >> m_tileOffset >> ir >> ig >> ib;
		in >> m_levelWidth >> m_levelHeight;
	}
	else
	{
		std::cout << "Unable to open file " << filename << std::endl;
	}

	SparseMatrix tiles(m_levelHeight, m_levelWidth);
	m_tiles = tiles;

	// Cast keying colors manually!
	m_keyR = (unsigned char)ir;
	m_keyG = (unsigned char)ib;
	m_keyB = (unsigned char)ig;

	// Load texture
	std::cout << texFileName << std::endl;
	m_texture = loadTexture(texFileName, m_keyR, m_keyG, m_keyB);

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
					target.y = i * m_tileHeight - m_camera.y();


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

WorldProperty& Level::physics()
{
	return m_levelPhysics;
}

void Level::getSurroundingTiles(Vector2f pos, int width, int height, Camera &cam, Vector2i *tiles)
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

void Level::checkAndResolveCollision(Actor* player)
{
	SDL_Rect tileRect;
	SDL_Rect spriteRect;
	SDL_Rect intersectionRect;
	Vector2f desiredPosition;
	Vector2i surroundingTiles[8];
	int n, i ,j;

	//Convert the player sprite's screen position to global position
	Vector2f global_pos = player->position() + Vector2f(m_camera.position().x(), m_camera.position().y());

	// Set desired position to new position
	desiredPosition = global_pos;


	// Check if sprite intersects with one of its surrounding tiles
	getSurroundingTiles(global_pos, player->w(), player->h(), m_camera, surroundingTiles);
	int d_i, d_j;
	int f_i, f_j;
	player->setOnGround(false);
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

	if(f_i < m_levelHeight && f_j < m_levelWidth)
	{
		if(m_tiles[f_i][f_j] > 0) player->setOnGround(true);
	}


	if(d_i < m_levelHeight && d_j < m_levelWidth )
	{
		if(m_tiles[d_i][d_j] > 0) player->setOnGround(true);
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



					if(n == 6)
					{
						player->setOnGround(true);
					}

					// Handle pose correction cases
					if(n == 4)
					{
						desiredPosition.setX(desiredPosition.x() - intersectionRect.w);
					}
					else if(n == 1)
					{
						desiredPosition.setY(desiredPosition.y() + intersectionRect.h);
						player->setJumping(false);
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
								if( (n == 0) || (n == 2) )
								{
									player->setJumping(false);
								}
							}
						}
					}
				}
			}
		}
	}

	player->setPosition(Vector2f(desiredPosition.x() - m_camera.position().x(), desiredPosition.y() - m_camera.position().y()));

}

/*void Level::updatePlayerPosition(int move, bool jump, double dt)
{
	m_player->nextFrame();
	if(dt > 0)
	{

		if(dt > 0 && jump && m_player->onGround())
		{
			m_player->setJumping(true);
		}

		Vector2f d_gravity;
		Vector2f d_move;

		d_gravity = m_levelPhysics.gravity() * dt;

		if(move != 0)
		{
			d_move = (m_player->physics().moveForce() * dt) * move;
		}
		else
		{
			d_move.setX(0);
			d_move.setY(0);
		}

		// Update velocity
		m_player->physics().setVelocity(m_player->physics().velocity() + d_move + d_gravity);

		// Add jumping momentum
		if(m_player->jumping())
		{
			m_player->physics().velocity().setY(
					m_player->physics().velocity().y() + (m_player->physics().jumpForce().y() * dt) );
		}

		// Damp velocity according to extrinsic level damping
		m_player->physics().setVelocity(m_player->physics().velocity() * m_levelPhysics.damping());

		// Clamp velocities
		if(m_player->physics().velocity().x() > m_player->physics().maxRunVelocity() * dt)
		{
			m_player->physics().setVelocity(Vector2f(m_player->physics().maxRunVelocity() * dt,
													 m_player->physics().velocity().y()));
		}

		if(m_player->physics().velocity().x() < -m_player->physics().maxRunVelocity() * dt)
		{
			m_player->physics().setVelocity(Vector2f(-m_player->physics().maxRunVelocity() * dt,
													 m_player->physics().velocity().y()));
		}

		if(m_player->physics().velocity().y() > m_player->physics().maxFallVelocity() * dt)
		{
			m_player->physics().setVelocity(
					Vector2f(m_player->physics().velocity().x(), m_player->physics().maxFallVelocity() * dt));
		}

		if(m_player->physics().velocity().y() < -m_player->physics().maxJumpVelocity() * dt)
		{
			m_player->physics().setVelocity(
					Vector2f(m_player->physics().velocity().x(), -m_player->physics().maxJumpVelocity() * dt));
		}

		// Set new player position
		m_player->physics().setPosition(m_player->physics().position() + m_player->physics().velocity());


		// Move camera if player position exceeds window with / 2
		m_camera.position().setX(m_player->position().x() - m_levelWidth / 2 + m_player->w());
		if(m_camera.position().x() < 0)
		{
			m_camera.position().setX(0);
		}

		// Stop jumping at maximum jumping height
		if(fabs(m_player->physics().position().y() - m_player->jumpStart()) >= m_player->physics().maxJumpHeight())
		{
			m_player->setJumping(false);
		}

	}
} */




} /* namespace jumper */
