
#include <stdio.h>
#include <SDL.h>

SDL_Window* 	pWindow 		= NULL;
SDL_Surface*	pScreenSurface 	= NULL;

const int SCREEN_WIDTH 			= 640;
const int SCREEN_HEIGHT 		= 480;

int main(int argc, char** argv)
{
	/* Init SDL */
	if(SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		printf("SDL could not initialize: %s\n", SDL_GetError());
		return EXIT_FAILURE;
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
		return EXIT_FAILURE;
	}

	/* Get window surface */
	pScreenSurface = SDL_GetWindowSurface( pWindow );

	/* Swap buffers */
	SDL_UpdateWindowSurface( pWindow );

	/* Wait for 10 seconds */
	SDL_Delay(10000);

    return 0;
}
