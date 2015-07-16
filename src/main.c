
#include <stdio.h>
#include <SDL.h>

#include "jmpr.h"


int main(int argc, char** argv)
{
	SDL_Event e;
	int quit = 0;
	struct jmprTileSet* tileset;
	struct jmprSprite*  sprite;

	int moveX;
	int moveY;

	if(jmprInitSDL())
	{
		/* Load tiles and sprites */
		tileset = jmprLoadTileDefinitions(argv[1]);
		if(tileset == NULL)
		{
			printf("jmprMain: Unable to load tileset %s. Exiting...\n", argv[1]);
			return;
		}
		jmprPrintTiles(tileset);

		sprite = jmprLoadSprite(argv[2]);
		if(sprite == NULL)
		{
			printf("jmprMain: Unable to load sprite %s. Exiting...\n", argv[2]);
			return;
		}
		jmprSetSpritePosition(sprite, 100, 300);

		/* Start main loop and event handling */
		while(!quit)
		{

			moveX = 0;
			moveY = 0;
			/* Processs events, detect quit signal for window closing */
			while(SDL_PollEvent(&e))
			{
				if(e.type == SDL_QUIT)
				{
					quit = 1;
				}
				if(e.type == SDL_KEYDOWN)
				{
					if(e.key.keysym.sym == SDLK_LEFT)
					{
						moveX = -1;
					}
					else if(e.key.keysym.sym == SDLK_RIGHT)
					{
						moveX = 1;
					}
					else if(e.key.keysym.sym == SDLK_DOWN)
					{
						moveY = 1;
					}
					else if(e.key.keysym.sym == SDLK_UP)
					{
						moveY = -1;
					}

				}
			}

			/* Evaluate move commands */
			if(moveX)
			{
				jmprMoveSprite(sprite, RIGHT, moveX);
			}

			if(moveY)
			{
				jmprMoveSprite(sprite, DOWN, moveY);
			}

			jmprCheckAndResolveCollision(tileset, sprite);

			/* Clear screen */
			SDL_RenderClear( pRenderer );

			/* Render tiles and sprite */
			jmprRenderTiles(tileset);
			jmprRenderSprite(sprite);

			/* Update screen */
			SDL_RenderPresent( pRenderer );
		}
	}

	free(sprite);
	free(tileset);
	jmprClearSDL();


    return 0;
}
