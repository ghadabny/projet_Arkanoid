#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FPS 70.0
#define BRICK_WIDTH 32
#define BRICK_HEIGHT 16
#define BRICKS_PER_ROW 19
#define BRICK_ROWS 20

typedef enum {
    BRICK_NONE,
    BRICK_NORMAL,
    BRICK_HARD,
    BRICK_INDESTRUCTIBLE,
} BrickType;

typedef struct {
    BrickType type;  // Type of the brick (normal, hard, indestructible)
    int hitCount;    // Number of hits the brick has taken (for hard bricks)
    int color;       // Color index or identifier for the brick
    bool shouldAnimate; // Flag to indicate whether the brick should animate
    int animationFrame;
    int animationCounter; // Current frame of the animation
} Brick;

extern bool laserActive; // Indicates if the laser power-up is active

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

extern bool ballIsSticky;

extern int playerLives; // Add this line for player lives

#endif // GLOBALS_H
