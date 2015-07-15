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

SDL_Texture* jmprLoadTextureWithKey(const char* filename, unsigned char key_r, unsigned char key_g, unsigned char key_b)
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
	{
		/* Set keying color */
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, key_r, key_g, key_b ) );

		/* Create texture from surface pixels */
		newTexture = SDL_CreateTextureFromSurface( pRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError() );
		}

		/* Get rid of old loaded surface */
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

struct jmprSprite* jmprLoadSprite(const char* filename)
{
	struct jmprSprite* sprite;
	FILE* f_sprite;
	char texture_filename[512];

	sprite = (struct jmprSprite*)malloc(sizeof(struct jmprSprite));
	if(sprite == NULL)
	{
		printf("jmprLoadSprite: Unable to alloc memory for sprite.\n");
	}

	f_sprite = fopen(filename, "r");
	if(f_sprite == NULL)
	{
		printf("jmprLoadSprite: Unable to open file %s.\n", filename);
	}

	/* Read image file name and generate texture */
	fscanf(f_sprite, "%s", texture_filename);
	sprite->texture = jmprLoadTexture(texture_filename);

	/* Read additional sprite information */
	fscanf(f_sprite, "%d %d %d", &sprite->width, &sprite->height, &sprite->num_anim);
	sprite->current_anim = 0;

	return sprite;

}

void jmprRenderSprite(struct jmprSprite* s)
{
	SDL_Rect target;
	SDL_Rect source;

	target.x = s->pos.x;
	target.y = s->pos.y;
	target.w = s->width;
	target.h = s->height;

	/* Check animation status */
	if(s->current_anim > s->num_anim)
	{
		s->current_anim = 0;
	}

	/* Determine position of animation frame */
	source.x = s->current_anim * s->width;
	source.y = 0;
	source.w = s->width;
	source.h = s->height;

	/* Render current animation frame */
	SDL_RenderCopy( pRenderer, s->texture, &source, &target);
}

void jmprMoveSprite(struct jmprSprite* s,  int direction, int speed)
{
	switch(direction)
	{
	case UP 	: s->pos.y -= speed; break;
	case DOWN	: s->pos.y += speed; break;
	case LEFT	: s->pos.x -= speed; break;
	case RIGHT  : s->pos.x += speed; break;
	}
	s->current_anim++;

	if(s->current_anim >= s->num_anim)
	{
		s->current_anim = 0;
	}
}

void jmprSetSpritePosition(struct jmprSprite* s, int x, int y)
{
	s->pos.x = x;
	s->pos.y = y;
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
		return NULL;
	}

	/* Open given level file */
	f_level = fopen(filename, "r");

	if(f_level == NULL)
	{
		printf("jmprLoadTileDefinitions: Unagle to open file %s.\n", filename);
		return NULL;
	}

	/* Read filename of texture bitmap */
	fscanf(f_level, "%s", texture_filename);

	/* Read tile set meta information */
	fscanf(f_level, "%d %d %d %d %d %hhu %hhu %hhu",
		&tileset->tile_width,
		&tileset->tile_height,
		&tileset->tiles_per_row,
		&tileset->num_rows,
		&tileset->tile_offset,
		&tileset->key_r,
		&tileset->key_g,
		&tileset->key_b);

	/* Read dimensions of tile grid */
	fscanf(f_level, "%d %d", &tileset->width, &tileset->height);

	/* Allocate memory for tile grid */
	tileset->tiles = (int**)malloc(tileset->height * sizeof(int*));
	for(i = 0; i < tileset->height; i++)
	{
		tileset->tiles[i] = (int*)malloc(tileset->width * sizeof(int));
	}

	/* Read tile numbers in grid */
	for(i = 0; i < tileset->height; i++)
	{
		for(j = 0; j < tileset->width; j++)
		{
			fscanf(f_level, "%d", &tileset->tiles[i][j]);
		}
	}

	/* Alloc texture */
	tileset->texture = jmprLoadTextureWithKey(texture_filename, tileset->key_r, tileset->key_g, tileset->key_b);

	return tileset;
}

void jmprRenderTiles(struct jmprTileSet* t)
{
	int i;
	int j;
	int tile_index;
	int col, row;
	SDL_Rect target;
	SDL_Rect source;

	/* Set target / source width and height to tile size,
	 * they never change
	 */
	target.w = t->tile_width;
	target.h = t->tile_height;

	source.w = t->tile_width;
	source.h = t->tile_height;


	for(i = 0; i < t->height; i++)
	{
		for(j = 0; j < t->width; j++)
		{
			tile_index = t->tiles[i][j] - 1;
			if(tile_index >= 0)
			{
				/* Compute the position of the target on the screen */
				target.x = j * t->tile_width;
				target.y = i * t->tile_height;

				/* Compute the position of the source pixel data
				 * within the texture (no offset for first tiles)
				 */
				row = tile_index / t->tiles_per_row;
				col = tile_index % t->tiles_per_row;

				source.x = col * t->tile_width;
				if(col > 0)
				{
					source.x += col * t->tile_offset;
				}

				source.y = row * t->tile_height;
				if(row > 0)
				{
					source.y += row * t->tile_offset;
				}

				/* Copy pixel date to correct position */
				SDL_RenderCopy( pRenderer, t->texture, &source, &target);
			}
		}
	}
}
