#ifndef SCORE_H
#define SCORE_H

#include <SDL.h>
#include "globals.h"

// Adjust these to match the size of a single character in your font sprite sheet
#define FONT_WIDTH 16 // Width of a character in the sprite sheet
#define FONT_HEIGHT 24 // Height of a character in the sprite sheet

// Global score variables
extern int currentScore;
extern int highScore;
extern SDL_Surface* scoreFontSpriteSheet;

// Function declarations
void initializeScore();
void updateScore(int points);
void updateHighScore();
void drawScore(SDL_Surface *surface, int score, int x, int y);
void drawText(SDL_Surface *surface, const char *text, int x, int y);
void drawScoreboard(SDL_Surface* surface, int currentScore, int highScore);

#endif // SCORE_H
