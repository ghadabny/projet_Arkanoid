#include "globals.h"

int playerLives = 3; // Initial number of lives
bool ballIsSticky = false; // Initial state is not sticky
bool laserActive = false; 

Brick bricks[BRICK_ROWS][BRICKS_PER_ROW];
Ball ball = {0};
SDL_Window* pWindow = NULL;
SDL_Surface* win_surf = NULL;
SDL_Surface* plancheSprites = NULL;
SDL_Surface* brickSpriteSheet = NULL;

int score = 0;
int currentLevel = 1;
bool isGamePaused = false;

Uint64 prev = 0, now = 0;
double delta_t = 0.0;
int x_vault = 0;

// Initialize these SDL_Rects based on their intended values
SDL_Rect srcBg = { 0, 128, 96, 128 };
SDL_Rect srcBall = { 0, 96, 24, 24 };
SDL_Rect scrVaiss = { 128, 0, 128, 32 };

int SCOREBOARD_HEIGHT = 50; 

