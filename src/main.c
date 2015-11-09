
#include <stdio.h>
#include <SDL.h>

#include "jmpr.h"


int main(int argc, char** argv)
{
	SDL_Event e;
	int quit = 0;
	struct jmprLevel* tileset;

	if(jmprInitSDL())
	{
		/* Load tiles and sprites */
		tileset = jmprLoadTileDefinitions(argv[1]);
		if(tileset == NULL)
		{
			printf("jmprMain: Unable to load tileset %s.\n", argv[1]);
		}


		/* Start main loop and event handling */
		while(!quit)
		{
			/* Processs events, detect quit signal for window closing */
			while(SDL_PollEvent(&e))
			{
				if(e.type == SDL_QUIT)
				{
					quit = 1;
				}
			}

			/* Clear screen */
			SDL_RenderClear( pRenderer );

			/* Render tiles and sprite */
			jmprRenderTiles(tileset);

			/* Update screen */
			SDL_RenderPresent( pRenderer );
		}
	}

	free(tileset);
	jmprClearSDL();

    return 0;
}
