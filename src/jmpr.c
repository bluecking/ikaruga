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

	 //Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
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

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* jmprLoadTexture(const char* filename)
{
	/* The loaded texture */
	SDL_Texture* newTexture = NULL;

	/* Load image at specified path */
	SDL_Surface* loadedSurface = IMG_Load(filename);
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError() );
	}
	else
	{ //Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( pRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError() );
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	return newTexture;
}

void jmprPrintTiles(struct jmprTileSet* t)
{
	int i, j;
	printf("Tile set meta info: %d %d %d %d %d\n",
		t->tile_width, t->tile_height, t->tiles_per_row, t->num_rows, t->tile_offset);
	printf("Tile set dimensions: %d %d\n", t->width, t->height);

	for(i = 0; i < t->width; i++)
	{
		for(j = 0; j < t->height; j++)
		{
			printf("%3d", t->tiles[i][j]);
		}
		printf("\n");
	}
}

struct jmprTileSet* jmprLoadTileDefinitions(const char* filename)
{
	/* Variable declarations */
	struct jmprTileSet* tileset;
	FILE* f_level;
	char texture_filename[512];
	int i, j;

	/* Alloc memory for tileset struct */
	tileset = (struct jmprTileSet*)malloc(sizeof(struct jmprTileSet));

	if(tileset == NULL)
	{
		printf("jmprLoadTileDefinitions: Unable to alloc memory for tileset struct.\n");
	}

	/* Open given level file */
	f_level = fopen(filename, "r");

	/* Read filename of texture bitmap */
	fscanf(f_level, "%s", texture_filename);

	/* Read tile set meta information */
	fscanf(f_level, "%d %d %d %d %d",
		&tileset->tile_width,
		&tileset->tile_height,
		&tileset->tiles_per_row,
		&tileset->num_rows,
		&tileset->tile_offset);

	/* Read dimensions of tile grid */
	fscanf(f_level, "%d %d", &tileset->width, &tileset->height);

	/* Allocate memory for tile grid */
	tileset->tiles = (int**)malloc(tileset->width * sizeof(int*));
	for(i = 0; i < tileset->height; i++)
	{
		tileset->tiles[i] = (int*)malloc(tileset->height * sizeof(int));
	}

	/* Read tile numbers in grid */
	for(i = 0; i < tileset->width; i++)
	{
		for(j = 0; j < tileset->height; j++)
		{
			fscanf(f_level, "%d", &tileset->tiles[i][j]);
		}
	}

	/* Alloc texture */
	tileset->texture = jmprLoadTexture(texture_filename);

	return tileset;
}

