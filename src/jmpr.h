/*
 * jmpr.h
 *
 *  Created on: Jul 13, 2015
 *      Author: Thomas Wiemann
 */

#ifndef SRC_JMPR_H_
#define SRC_JMPR_H_

#include <SDL.h>
#include <SDL_image.h>

/*****************************************************************************/
/* GLOBAL VARIABLES                                                          */
/*****************************************************************************/

/* SDL related global variables */
extern SDL_Window* 		pWindow;
extern SDL_Renderer*	pRenderer;

/* Screen resolution and stuff */
#define SCREEN_WIDTH 	1024
#define SCREEN_HEIGHT 	786

/* Tile related stuff */
#define TILE_WIDTH		16
#define TILE_HEIGHT		16
#define TILE_OFFSET		1

/*****************************************************************************/
/* STRUCTURES													  			 */
/*****************************************************************************/

struct jmprLevel
{
	int tile_width;			/* With of the tiles within the tile set bitmap  */
	int tile_height;		/* Height of the tile within the tile set bitmap */
	int tile_offset;		/* Offset between the tiles (in pixels)          */
	int num_rows;			/* Number of tile rows in the bitmap 			 */
	unsigned char key_r;	/* R component of the keying color               */
	unsigned char key_g;	/* G component of the keying color               */
	unsigned char key_b;	/* B component of the keying color               */
	int tiles_per_row;		/* Number of tiles per row                       */
	int level_width;		/* Number of tiles per row in the tile array     */
	int level_height;		/* Number of rows in the tile array              */
	SDL_Texture* texture;   /* A SDL_Texture struct containing the bitmap    */
	int** tiles;            /* An array containing tile indices              */
};


/*****************************************************************************/
/* FUNCTION PROTOTYPES                                                       */
/*****************************************************************************/

/**
 * @brief Initialize SDL engine
 */
int jmprInitSDL();

/**
 * @brief Close SDL engine
 */
int jmprClearSDL();

/***
 * Loads a SDL_Texture from the given filename.
 *
 * @param 	file	An image file from which a texture is created.
 * @return	A pointer to a SDL_Texture struct if the texture was
 * 			creates successfully. A null pointer otherwise.
 */
SDL_Texture* jmprLoadTexture(const char* file);

/***
 * Loads a SDL_Texture from the given filename and sets the transparency
 * color to the color defined by \ref key_r, \ref key_b and \ref key_b.
 *
 * @param 	file	An image file from which a texture is created.
 * @param	key_r	Red component of the key color.
 * @param	key_g	Green component of the key color.
 * @param	key_b	Blue component of the key color.
 * @return	A pointer to a SDL_Texture struct if the texture was
 * 			creates successfully. A null pointer otherwise.
 */
SDL_Texture* jmprLoadTextureWithKey(
		const char* file,
		unsigned char key_r,
		unsigned char key_g,
		unsigned char key_b);

/***
 * Renders a tileset.
 * @param 	tileset	A tileset to render.
 */
void jmprRenderTiles(struct jmprLevel* tileset);

/**
 * Loads a tileset from the given file.
 *
 * @param 	filename	A file defining a tile set.
 * @return	A pointer to jmprTileSet struct (if loaded successfully)
 * 			or a null pointer if the given file could not be
 * 			parsed.
 */
struct jmprLevel* jmprLoadTileDefinitions(const char* filename);


#endif /* SRC_JMPR_H_ */
