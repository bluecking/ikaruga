/*
 * Level.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "Level.hpp"

#include <iostream>
#include <fstream>
#include <SDL_image.h>

namespace jumper
{


Level::Level(SDL_Renderer* renderer, std::string filename)
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
	m_renderer = renderer;

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

	// Cast keying colors manually!
	m_keyR = (unsigned char)ir;
	m_keyG = (unsigned char)ib;
	m_keyB = (unsigned char)ig;

	// Load texture
	m_texture = loadTexture(texFileName);

	if(!m_texture)
	{
		std::cout << "Unable to load texture " << texFileName << std::endl;
	}

	// Alloc tile set memory
	m_tiles = new int*[m_levelHeight];
	for(int i = 0; i < m_levelHeight; i++)
	{
		m_tiles[i] = new int[m_levelWidth];
	}

	// Read tile indices
	for(int i = 0; i < m_levelHeight; i++)
	{
		for(int j = 0; j < m_levelWidth; j++)
		{
			int tileID;
			in >> tileID;
			m_tiles[i][j] = tileID;
		}
	}

	in.close();
}

void Level::render(Camera& cam)
{
	if(m_renderer && m_texture)
	{
		int i;
		int j;
		int tile_index;
		int col, row;
		SDL_Rect target;
		SDL_Rect source;

		/* Set target / source width and height to tile size,
		 * they never change
		 */
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
					/* Compute the position of the target on the screen */
					target.x = j * m_tileWidth + cam.x();
					target.y = i * m_tileHeight + cam.y();

					/* Compute the position of the source pixel data
					 * within the texture (no offset for first tiles)
					 */
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

					/* Copy pixel date to correct position */
					SDL_RenderCopy( m_renderer, m_texture, &source, &target);
				}
			}
		}
	}
}

Level::~Level()
{
	// Free tile array
	if(m_tiles)
	{
		for(int i = 0; i < m_levelHeight; i++)
		{
			delete[] m_tiles[i];
		}
	}
	delete[] m_tiles;

	// Free texture resources
	SDL_DestroyTexture(m_texture);
}

SDL_Texture* Level::loadTexture(std::string texFileName)
{
	// The loaded texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(texFileName.c_str());
	if( loadedSurface == NULL )
	{
		std::cout << "Unable to load image! SDL_image Error: " <<  IMG_GetError() << std::endl;
	}
	else
	{
		// Set keying color
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, m_keyR, m_keyG, m_keyB) );

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( m_renderer, loadedSurface );
		if( newTexture == NULL )
		{
			std::cout <<  "Unable to create texture from! SDL Error: " << texFileName <<  SDL_GetError() << std::endl;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	return newTexture;

}

} /* namespace jumper */
