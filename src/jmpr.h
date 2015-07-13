/*
 * jmpr.h
 *
 *  Created on: Jul 13, 2015
 *      Author: twiemann
 */

#ifndef SRC_JMPR_H_
#define SRC_JMPR_H_

#include "SDL.h"

/* SDL related global variables */
SDL_Window* 	pWindow 		= NULL;
SDL_Surface*	pScreenSurface 	= NULL;

/* Screen resolution and stuff */
const int SCREEN_WIDTH 			= 640;
const int SCREEN_HEIGHT 		= 480;

/* Tile related stuff */
const int TILE_WIDTH 	= 16;
const int TILE_HEIGHT	= 16;
const int TILE_OFFSET	= 1;




#endif /* SRC_JMPR_H_ */
