/*
 * jmpr.h
 *
 *  Created on: Jul 13, 2015
 *      Author: twiemann
 */

#ifndef SRC_JMPR_H_
#define SRC_JMPR_H_

#include "SDL.h"

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
/* FUNCTION PROTOTYPES                                                      */
/****************************************************************************/

int jmprInitSDL();
int jmprClearSDL();



#endif /* SRC_JMPR_H_ */
