#include "init.h"


void initBricks() {
    // Initialize bricks as NONE
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICKS_PER_ROW; j++) {
            bricks[i][j].type = BRICK_NONE;
            bricks[i][j].hitCount = 0;
        }
    }
}

void init()
{
	pWindow = SDL_CreateWindow("Arknoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);
	plancheSprites = SDL_LoadBMP("./sprites.bmp");
	brickSpriteSheet = SDL_LoadBMP("../Arkanoid_sprites.bmp");
    if (brickSpriteSheet == NULL) {
        printf("Unable to load brick sprite sheet: %s\n", SDL_GetError());
        exit(1); // Exit if the sprite sheet failed to load
    }
	SDL_SetColorKey(plancheSprites, true, 0);  // 0: 00/00/00 noir -> transparent

	ball.x = win_surf->w / 2;
	ball.y = win_surf->h / 2;
	ball.vx = 1.0;
	ball.vy = 1.4;

	now = SDL_GetPerformanceCounter();
	initBricks(); 
    //loadLevel();
    // Initialize the score system
    //initializeScore();
}
