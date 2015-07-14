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

/****************************************************************************/
/* GLOBAL VARIABLES                                                         */
/****************************************************************************/

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

/****************************************************************************/
/* STRUCTURES																*/
/****************************************************************************/

struct jmprTileSet
{
	int tile_width;
	int tile_height;
	int tile_offset;
	int num_rows;
	unsigned char key_r;
	unsigned char key_g;
	unsigned char key_b;
	int tiles_per_row;
	int width;
	int height;
	SDL_Texture* texture;
	int** tiles;
};

/****************************************************************************/
/* FUNCTION PROTOTYPES                                                      */
/****************************************************************************/

/**
 * @brief Initialize SDL engine
 */
int jmprInitSDL();

/**
 * @brief Close SDL engine
 */
int jmprClearSDL();


SDL_Texture* jmprLoadTexture(const char* file);
SDL_Texture* jmprLoadTextureWithKey(const char* file, unsigned char key_r, unsigned char key_g, unsigned char key_b);
void jmprRenderTiles(struct jmprTileSet*);
void jmprPrintTiles(struct jmprTileSet*);
struct jmprTileSet* jmprLoadTileDefinitions(const char* filename);


#endif /* SRC_JMPR_H_ */
