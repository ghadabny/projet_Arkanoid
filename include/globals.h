#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FPS 70.0
#define BRICK_WIDTH 32
#define BRICK_HEIGHT 16
#define BRICKS_PER_ROW 10
#define BRICK_ROWS 10

typedef enum {
    BRICK_NONE,
    BRICK_NORMAL,
    BRICK_HARD,
    BRICK_INDESTRUCTIBLE,
} BrickType;

typedef struct {
    BrickType type;
    int hitCount;
    int color;
} Brick;

typedef struct {
    double x;
    double y;
    double vx;
    double vy;
} Ball;


extern Brick bricks[BRICK_ROWS][BRICKS_PER_ROW];
extern Ball ball;
extern SDL_Window* pWindow;
extern SDL_Surface* win_surf;
extern SDL_Surface* plancheSprites;
extern SDL_Surface* brickSpriteSheet;

// Declarations
extern SDL_Rect srcBg;
extern SDL_Rect srcBall;
extern SDL_Rect scrVaiss;

extern int score;
extern int currentLevel;
extern bool isGamePaused;

extern Uint64 prev, now; // timers
extern double delta_t;  // durée frame en ms
extern int x_vault;

extern int SCOREBOARD_HEIGHT; 

#endif // GLOBALS_H
