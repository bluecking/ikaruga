
#include <stdio.h>
#include <SDL.h>

#include "jmpr.h"


int main(int argc, char** argv)
{
	SDL_Event e;
	int quit = 0;
	struct jmprTileSet* tileset;
	struct jmprSprite*  sprite;
	jmprPhysics* physics;

	int moveX;
	int moveY;
	int jump;

	Uint32 startTicks;
	double renderTime;
	const Uint8* currentKeyStates;

	renderTime = 0.0;

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

		physics = jmprInitPhysics();
		jmprSetSpritePosition(sprite, 400, 200);

		/* Start main loop and event handling */
		while(!quit)
		{
			startTicks = SDL_GetTicks();
			moveX = 0;
			moveY = 0;
			jump = 0;
			/* Processs events, detect quit signal for window closing */
			while(SDL_PollEvent(&e))
			{
				if(e.type == SDL_QUIT)
				{
					quit = 1;
				}
			}

			currentKeyStates = SDL_GetKeyboardState( NULL );

			if( currentKeyStates[ SDL_SCANCODE_UP ] )
			{
				moveY = -1;
			}
			if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
			{
				moveY = 1;
			}
			if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
			{
				moveX = -1;
			}
			if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
			{
				moveX = 1;
			}
			if( currentKeyStates[ SDL_SCANCODE_SPACE ])
			{
				jump = 1;
			}

			//if(sprite->onGround) printf("GROUND\n"); else printf("FALLING\n");
			jmprUpdateSprite(physics, sprite, moveX, jump, renderTime);
			jmprCheckAndResolveCollision(tileset, sprite);

			/* Clear screen */
			SDL_RenderClear( pRenderer );

			/* Render tiles and sprite */
			jmprRenderTiles(tileset);
			jmprRenderSprite(sprite);

			/* Update screen */
			SDL_RenderPresent( pRenderer );
			renderTime = (SDL_GetTicks() - startTicks) / 1000.0;
		}
	}

	free(sprite);
	free(tileset);
	jmprClearSDL();


    return 0;
}
