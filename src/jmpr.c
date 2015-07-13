#include "jmpr.h"

/* SDL related global variables */
SDL_Window* 	pWindow 		= NULL;
SDL_Renderer*	pRenderer		= NULL;


int jmprInitSDL()
{
	/* Init SDL */
	if(SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		printf("SDL could not initialize: %s\n", SDL_GetError());
		return 0;
	}

	/* Generate SDL main window */
	pWindow = SDL_CreateWindow(
			"Jumper Main Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN );

	if(pWindow == NULL)
	{
		printf("SDL window could not be generated: %s\n", SDL_GetError());
		return 0;
	}

	/* Create renderer for the SDL main window */
	pRenderer = SDL_CreateRenderer( pWindow, -1, SDL_RENDERER_ACCELERATED );

	if(pRenderer == NULL)
	{
		printf("SDL could not generate renderer: %s\n", SDL_GetError());
		return 0;
	}

	/* Set background color for renderer */
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);

	return 1;
}

int jmprClearSDL()
{
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;

	SDL_DestroyRenderer(pRenderer);
	pRenderer = NULL;

	SDL_Quit();
}
