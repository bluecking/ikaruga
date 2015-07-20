#include "jmpr.h"

#include <math.h>

/* SDL related global variables */
SDL_Window* 	pWindow 		= NULL;
SDL_Renderer*	pRenderer		= NULL;


jmprPhysics* jmprInitPhysics()
{
	jmprPhysics* p;
	p = (jmprPhysics*)malloc(sizeof(jmprPhysics));

	p->gravity.x 	= 0.0;
	p->gravity.y 	= 400.0;

	p->move.x		= 800.0;
	p->move.y		= 0.0;

	p->jump.y		= -440;
	p->jump.x 		= 0.0;

	p->damping.x	= 0.99;
	p->damping.y	= 1.0;

	p->maxVelJmp	= 300.0;
	p->maxVelRun	= 120.0;
	p->maxVelFall	= 250.0;

	p->jumpHeight	= 90;
	return p;
}



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
	sprite->vel.x = 0.0;
	sprite->vel.y = 0.0;
	sprite->jumping = 0;
	sprite->jumpStart = 0;
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

void jmprGetSurroundingTiles(struct jmprTileSet* set, struct jmprSprite* s, jmprVecI tiles[])
{
	jmprVecI gridPos;

	/* Determine x and y position of the sprite within the grid */
	gridPos.x = floor((s->pos.x + 0.5 * s->width) / set->tile_width);
	gridPos.y = floor((s->pos.y  + 0.5 * s->height) / set->tile_height);

	/* Get the surrounding tiles in "priority" order, i.e., we want
	 * check some collisions like left befire we check the others
	 */
	tiles[0].x = gridPos.x - 1;
	tiles[0].y = gridPos.y - 1;

	tiles[1].x = gridPos.x;
	tiles[1].y = gridPos.y - 1;

	tiles[2].x = gridPos.x + 1;
	tiles[2].y = gridPos.y - 1;

	tiles[3].x = gridPos.x - 1;
	tiles[3].y = gridPos.y;

	tiles[4].x = gridPos.x + 1;
	tiles[4].y = gridPos.y;

	tiles[5].x = gridPos.x - 1;
	tiles[5].y = gridPos.y + 1;

	tiles[6].x = gridPos.x;
	tiles[6].y = gridPos.y + 1;

	tiles[7].x = gridPos.x + 1;
	tiles[7].y = gridPos.y + 1;

}

void jmprCheckAndResolveCollision(struct jmprTileSet* set, struct jmprSprite* s)
{
	SDL_Rect tileRect;
	SDL_Rect spriteRect;
	SDL_Rect intersectionRect;
	jmprVecF desiredPosition;
	jmprVecI surroundingTiles[8];
	int n, i ,j;

	/* Set desired position to new position */
	desiredPosition.x = s->pos.x;
	desiredPosition.y = s->pos.y;


	/* Check if sprite intersects with one of its surrounding tiles */
	jmprGetSurroundingTiles(set, s, surroundingTiles);
	int d_i, d_j;
	int f_i, f_j;
	s->onGround = 0;
	f_i = surroundingTiles[6].y;
	f_j = surroundingTiles[6].x;

	if(s->vel.x > 0)
	{
		d_i = surroundingTiles[7].y;
		d_j = surroundingTiles[7].x;
	}
	else
	{
		d_i = surroundingTiles[5].y;
		d_j = surroundingTiles[5].x;
	}

	if(f_i < set->height && f_j < set->width)
	{
		if(set->tiles[f_i][f_j] > 0) s->onGround = 1;
	}


	if(d_i < set->height && d_j < set->width)
	{
		if(set->tiles[d_i][d_j] > 0) s->onGround = 1;
	}


	for(n = 0; n < 8; n++)
	{
		j = surroundingTiles[n].x;
		i = surroundingTiles[n].y;

		/* Check, if tile coordinates are valid */
		if( (i >= 0) && (i < set->height) && (j >= 0) && (j < set->width) )
		{


			if(set->tiles[i][j] > 0)
			{

				/* Get SDL rect for current tile and sprite and check intersection */
				tileRect.y = i * set->tile_height;
				tileRect.x = j * set->tile_width;
				tileRect.w = set->tile_width;
				tileRect.h = set->tile_height;

				spriteRect.x = desiredPosition.x;
				spriteRect.y = desiredPosition.y;
				spriteRect.w = s->width;
				spriteRect.h = s->height;

				if(SDL_IntersectRect(&tileRect, &spriteRect, &intersectionRect))
				{
					//printf("n:%3d index: %3d @intersects (%3d,%3d)\n", n, set->tiles[i][j], intersectionRect.w, intersectionRect.h);

					if(n >= 5)
					{
						s->onGround = 1;
					}

					/* Handle pose correction cases */
					if(n == 4)
					{
						desiredPosition.x = desiredPosition.x - intersectionRect.w;
					}
					else if(n == 1)
					{
						desiredPosition.y = desiredPosition.y + intersectionRect.h;
					}
					else if(n == 3)
					{
						desiredPosition.x = desiredPosition.x + intersectionRect.w;
					}
					else if(n == 6)
					{
						desiredPosition.y = desiredPosition.y - intersectionRect.h;
					}
					else
					{
						if(intersectionRect.w >= 2 && intersectionRect.h >= 2)
						{
							if(intersectionRect.w > intersectionRect.h)
							{
								if( (n == 5) || (n == 7))
								{
									desiredPosition.y = desiredPosition.y - intersectionRect.h;
								}
								else
								{
									desiredPosition.y = desiredPosition.y + intersectionRect.h;
								}
							}
							else
							{
								if( (n == 2) || (n == 7))
								{
									desiredPosition.x = desiredPosition.x - intersectionRect.w;
								}
								else
								{
									desiredPosition.x = desiredPosition.x + intersectionRect.w;
								}
							}
						}
					}
				}
			}
		}
	}

	s->pos.x = desiredPosition.x;
	s->pos.y = desiredPosition.y;

}

void jmprUpdateSprite(jmprPhysics* p, struct jmprSprite* s, int move, int jump, double dt)
{
	s->current_anim++;

		if(s->current_anim >= s->num_anim)
		{
			s->current_anim = 0;
		}
	//printf("Pos: %3f %3f, Vel: %3f %3f %3d\n", s->pos.x, s->pos.y, s->vel.x, s->vel.y, s->onGround);
	if(dt > 0)
	{
		jmprVecI stiles[7];
		{
			if(dt > 0 && jump && s->onGround)
			{
				s->jumping = 1;
				s->jumpStart = s->pos.y;
				printf("JUMP\n");
			}

			jmprVecF d_gravity;
			jmprVecF d_move;

			d_gravity.x = p->gravity.x * dt;
			d_gravity.y = p->gravity.y * dt;

			if(move != 0)
			{
				d_move.x = move * p->move.x * dt;
				d_move.y = move * p->move.y * dt;
			}
			else
			{
				d_move.x = 0.0;
				d_move.y = 0.0;
			}

			s->vel.x = s->vel.x + d_move.x + d_gravity.x;
			s->vel.y = s->vel.y + d_move.y + d_gravity.y;

			if(s->jumping)
			{
				s->vel.y += p->jump.y * dt;
				printf("INC JUMP: %f %f\n", p->jump.y * dt, s->vel.y);
			}

			s->vel.x *= p->damping.x;
			s->vel.y *= p->damping.y;

			/* Clamp velocities */
			if(s->vel.x >  p->maxVelRun * dt) s->vel.x = p->maxVelRun * dt;
			if(s->vel.x < -p->maxVelRun * dt) s->vel.x = -p->maxVelRun * dt;

			if(s->vel.y >  p->maxVelFall * dt) s->vel.y = p->maxVelFall * dt;
			if(s->vel.y < -p->maxVelJmp * dt)  s->vel.y = -p->maxVelJmp * dt;

			s->pos.x += s->vel.x;
			s->pos.y += s->vel.y;

			printf("DIFF: %f\n", fabs(s->pos.y - s->jumpStart));
			if(fabs(s->pos.y - s->jumpStart) >= p->jumpHeight)
			{
				s->jumping = 0;
			}


			//printf("Pos: %3f %3f, Vel: %3f %3f %3d\n", s->pos.x, s->pos.y, s->vel.x, s->vel.y, s->onGround);
		}
	}


}
