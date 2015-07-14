
#include <stdio.h>
#include <SDL.h>

#include "jmpr.h"


int main(int argc, char** argv)
{
	SDL_Event e;
	int quit = 0;
	struct jmprTileSet* tileset;



	if(jmprInitSDL())
	{
		tileset = jmprLoadTileDefinitions(argv[1]);
		jmprPrintTiles(tileset);

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

			/* Render tiles */
			jmprRenderTiles(tileset);

			/* Update screen */
			SDL_RenderPresent( pRenderer );
		}
	}

	jmprClearSDL();

    return 0;
}
