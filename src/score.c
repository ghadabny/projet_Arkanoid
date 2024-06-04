#include "score.h"
#include "globals.h"
#include <stdio.h>
#include <string.h>

int currentScore = 0;
int highScore = 0;
SDL_Surface* scoreFontSpriteSheet = NULL;

// Initialize score system
void initializeScore() {
    scoreFontSpriteSheet = SDL_LoadBMP("../Arkanoid_ascii.bmp");
    if (scoreFontSpriteSheet == NULL) {
        printf("Unable to load score font sprite sheet: %s\n", SDL_GetError());
        exit(1); // Exit if the sprite sheet failed to load
    }
    SDL_SetColorKey(scoreFontSpriteSheet, SDL_TRUE, SDL_MapRGB(scoreFontSpriteSheet->format, 0, 0, 0));
    currentScore = 0;
    highScore = 0;

    FILE* file = fopen("highscore.txt", "r"); // Open the high score file for reading
    if (file != NULL) { // Ensure the file was opened successfully
        if (fscanf(file, "%d", &highScore) != 1) {
            highScore = 0; // If reading fails, default the highScore to 0
        }
        fclose(file); // Close the file
    } else {
        highScore = 0; // If the file doesn't exist, default the highScore to 0
    }
}

// Update the current score
void updateScore(int points) {
    currentScore += points;
    updateHighScore();
}

// Update the high score if current score exceeds it
void updateHighScore() {
    if (currentScore > highScore) {
        highScore = currentScore;

        FILE* file = fopen("highscore.txt", "w"); // Open the high score file for writing
        if (file != NULL) {
            fprintf(file, "%d", highScore); // Write the high score to the file
            fclose(file); // Close the file
        } else {
            printf("Failed to save high score!\n");
        }
    }
}

const int CHAR_WIDTH = 16;  // Width of a character in the sprite sheet
const int CHAR_HEIGHT = 24; 

const SDL_Rect srcRects[128] = {
    [0 ... 127] = {0, 0, 0, 0},  // Initialize all elements to zero

    // The following coordinates must be adjusted based on actual character positions on your sprite sheet.
    ['0' - 33] = {0 * FONT_WIDTH, 1.5 * FONT_HEIGHT, FONT_WIDTH, FONT_HEIGHT},
    ['1' - 33] = {2 * FONT_WIDTH, 1.5 * FONT_HEIGHT, FONT_WIDTH, FONT_HEIGHT},
    ['2' - 33] = {4 * CHAR_WIDTH, 1.5 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['3' - 33] = {6 * CHAR_WIDTH, 1.5 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['4' - 33] = {8 * CHAR_WIDTH, 1.5 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['5' - 33] = {10 * CHAR_WIDTH, 1.5 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['6' - 33] = {12 * CHAR_WIDTH, 1.5 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['7' - 33] = {14 * CHAR_WIDTH, 1.5 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['8' - 33] = {16 * CHAR_WIDTH, 1.5 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['9' - 33] = {18 * CHAR_WIDTH, 1.5 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},

    ['S' - 33] = {6 * CHAR_WIDTH, 4.25 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['C' - 33] = {6 * CHAR_WIDTH, 2.95 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['O' - 33] = {30 * CHAR_WIDTH, 2.95 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['R' - 33] = {4 * CHAR_WIDTH, 4.25 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['E' - 33] = {10 * CHAR_WIDTH, 2.95 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['H' - 33] = {16 * CHAR_WIDTH, 2.95 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['I' - 33] = {18 * CHAR_WIDTH, 2.95 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['G' - 33] = {14 * CHAR_WIDTH, 2.95 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['H' - 33] = {16 * CHAR_WIDTH, 2.95 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    [':' - 33] = {20 * CHAR_WIDTH, 1.65 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['L' - 33] = {24 * CHAR_WIDTH, 2.95 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    ['V' - 33] = {12 * CHAR_WIDTH, 4.25 * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT},
    
    // ... Add definitions for the rest of the characters.
};

// Draw the score on the screen
void drawScore(SDL_Surface *surface, int score, int x, int y) {
    char scoreStr[12];
    sprintf(scoreStr, "%d", score);
    int scoreLength = strlen(scoreStr);

    // Calculate total score width
    int scoreWidth = scoreLength * FONT_WIDTH;

    // Adjust x-coordinate for right alignment
    x -= scoreWidth;

    // Clear the score area - make sure the clear area width is large enough to cover the score
    SDL_Rect clearRect = {x, y, scoreWidth, FONT_HEIGHT};
    SDL_FillRect(surface, &clearRect, SDL_MapRGB(surface->format, 0, 0, 0));

    // Draw each character of the score string
    for (int i = 0; scoreStr[i] != '\0'; ++i) {
        char character = scoreStr[i];
        SDL_Rect srcRect = srcRects[character - '!']; // Adjusted to the sprite sheet character order
        SDL_Rect dstRect = {x + (i * FONT_WIDTH), y, FONT_WIDTH, FONT_HEIGHT};
        SDL_BlitSurface(scoreFontSpriteSheet, &srcRect, surface, &dstRect);
    }
}

// Draw text on the screen
void drawText(SDL_Surface *surface, const char *text, int x, int y) {
    int len = strlen(text);

    for (int i = 0; i < len; ++i) {
        char character = text[i];
        if (character - 33 < 0 || character - 33 >= 128) continue; // Skip if character is not in srcRects

        SDL_Rect srcRect = srcRects[character - 33]; // Adjusted to the sprite sheet character order
        SDL_Rect dstRect = {x + (i * FONT_WIDTH), y, FONT_WIDTH, FONT_HEIGHT};
        SDL_BlitSurface(scoreFontSpriteSheet, &srcRect, surface, &dstRect);
    }
}

// Clear and draw the scoreboard area at the top of the window
void drawScoreboard(SDL_Surface* surface, int currentScore, int highScore) {
    // Define the scoreboard area
    SDL_Rect scoreboardRect = {0, 0, surface->w, SCOREBOARD_HEIGHT};
    
    // Fill the scoreboard area with a solid color (e.g., dark grey)
    SDL_FillRect(surface, &scoreboardRect, SDL_MapRGB(surface->format, 0, 0, 0));
    
    // Draw the current score and high score on the scoreboard
    drawText(surface, "SCORE:", 5, SCOREBOARD_HEIGHT / 2 - FONT_HEIGHT / 2);
    drawScore(surface, currentScore, 150, SCOREBOARD_HEIGHT / 2 - FONT_HEIGHT / 2);
    drawText(surface, "HIGH SCORE:", surface->w - 270, SCOREBOARD_HEIGHT / 2 - FONT_HEIGHT / 2); // Adjust X as needed
    drawScore(surface, highScore, surface->w - 20, SCOREBOARD_HEIGHT / 2 - FONT_HEIGHT / 2);
    
    // Display remaining lives
    char livesText[20];
    sprintf(livesText, "LIVES: %d", playerLives);
    drawText(surface, livesText, 170, SCOREBOARD_HEIGHT / 2 - FONT_HEIGHT / 2);
}
