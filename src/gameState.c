// gameState.c
#include "gameState.h"
#include "powerup.h"
#include "init.h"

int colorLetterToIndex(char colorLetter) {
    switch(colorLetter) {
        case 'o': return 0;
        case 'b': return 1;
        case 'g': return 2;
        case 'n': return 3;
        case 'f': return 4;
        case 'r': return 5;
        case 'c': return 6;
        case 'p': return 7;
        case 'y': return 8;
        case 'd': return 9;
        case 't': return 10;
        case 's': return 11;
        case 'a': return 12;
        default: return -1;
    }
}

void loadLevel() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICKS_PER_ROW; j++) {
            bricks[i][j].type = BRICK_NONE;
            bricks[i][j].color = 0;
        }
    }

    char levelPath[50];
    sprintf(levelPath, "../levels/level%d.txt", currentLevel);
    FILE* levelFile = fopen(levelPath, "r");
    if (!levelFile) {
        perror("Failed to open level file");
        exit(1);
    }

    char line[BRICKS_PER_ROW * 2 + 2];
    int row = 0;

    while (fgets(line, sizeof(line), levelFile) != NULL && row < BRICK_ROWS) {
        int col = 0;
        for (int i = 0; line[i] != '\0' && col < BRICKS_PER_ROW; i++) {
            if (line[i] == '\n' || line[i] == '\r' || line[i] == ' ') continue;

            char brickTypeChar = line[i];
            char colorChar = (brickTypeChar == '1') ? line[i + 1] : '\0';

            if (brickTypeChar < '0' || brickTypeChar > '3') {
                continue;
            }

            if (brickTypeChar == '1' && colorLetterToIndex(colorChar) == -1) {
                continue;
            }

            switch (brickTypeChar) {
                case '0':
                    col++;
                    continue;
                case '1':
                    bricks[row][col].type = BRICK_NORMAL;
                    bricks[row][col].color = colorLetterToIndex(colorChar);
                    i++;
                    break;
                case '2':
                    bricks[row][col].type = BRICK_HARD;
                    bricks[row][col].color = 0;
                    break;
                case '3':
                    bricks[row][col].type = BRICK_INDESTRUCTIBLE;
                    bricks[row][col].color = 0;
                    break;
                default:
                    continue;
            }

            col++;
        }
        row++;
    }

    fclose(levelFile);
}


void loadNextLevel() {
    isGamePaused = true;
    currentLevel++;
    if (currentLevel > 5) {
        currentLevel = 1;
    }

    clearPowerUps();

    char levelPath[50];
    sprintf(levelPath, "../levels/level%d.txt", currentLevel);

    FILE* levelFile = fopen(levelPath, "r");
    if (levelFile == NULL) {
        printf("Congratulations! You've completed all available levels or an error occurred loading the next level.\n");
        exit(0);
    }
    fclose(levelFile);

    loadLevel();
    resetGameState();
    ball.vx *= 2;
    ball.vy *= 2;
}

void resetBallAndPaddle() {
    x_vault = (win_surf->w - scrVaiss.w) / 2;
    ball.x = x_vault + (scrVaiss.w / 2) - 12;
    ball.y = win_surf->h - scrVaiss.h - 25;
    ball.vx = 0;
    ball.vy = 0;
    printf("Ball and paddle reset. Ball position: (%f, %f)\n", ball.x, ball.y);
}

void resetGameState() {
    x_vault = (win_surf->w / 2) - (scrVaiss.w / 2);
    ball.x = x_vault + (scrVaiss.w / 2) - 12;
    ball.y = win_surf->h - scrVaiss.h - 25;
    ball.vx = 0;
    ball.vy = 0;
    // Add any additional game state resets here
}

void handleBallOutOfBounds() {
    printf("Ball out of bounds! Lives left: %d\n", playerLives - 1);
    playerLives--;
    if (playerLives > 0) {
        reinitGame();
        isGamePaused = true; // Pause the game until the player presses space to launch the ball again
        printf("Game reinitialized. Lives left: %d\n", playerLives);
    } else {
        printf("Game Over! No more lives.\n");
    }
}

void reinitGame() {
    x_vault = (win_surf->w - scrVaiss.w) / 2;  // Center the paddle
    ball.x = x_vault + (scrVaiss.w / 2) - 12; // Center the ball on the paddle
    ball.y = win_surf->h - scrVaiss.h - 25;   // Position the ball just above the paddle
    ball.vx = 0;  // Reset horizontal velocity
    ball.vy = 0;  // Reset vertical velocity
   // ballIsSticky = true; // Make the ball sticky to wait for space press
}