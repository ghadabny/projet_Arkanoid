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

void init() {
    pWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(pWindow);
    plancheSprites = SDL_LoadBMP("./sprites.bmp");
    brickSpriteSheet = SDL_LoadBMP("../Arkanoid_sprites.bmp");
    if (brickSpriteSheet == NULL) {
        printf("Unable to load brick sprite sheet: %s\n", SDL_GetError());
        exit(1); // Exit if the sprite sheet failed to load
    }
    SDL_SetColorKey(plancheSprites, true, 0);  // 0: 00/00/00 noir -> transparent

    x_vault = (win_surf->w - scrVaiss.w) / 2;  // Center the paddle

    ball.x = x_vault + (scrVaiss.w / 2) - 12; // Center the ball on the paddle
    ball.y = win_surf->h - scrVaiss.h - 25;   // Position the ball just above the paddle
    ball.vx = 0;  // Initial horizontal velocity
    ball.vy = 0;  // Initial vertical velocity

    now = SDL_GetPerformanceCounter();
    initBricks();
    loadLevel();
    playerLives = 3;  // Initialize the player's lives to 3
}
/*
void reinitGame() {
    x_vault = (win_surf->w - scrVaiss.w) / 2;  // Center the paddle
    ball.x = x_vault + (scrVaiss.w / 2) - 12; // Center the ball on the paddle
    ball.y = win_surf->h - scrVaiss.h - 25;   // Position the ball just above the paddle
    ball.vx = 0;  // Initial horizontal velocity
    ball.vy = 0;  // Initial vertical velocity
}*/