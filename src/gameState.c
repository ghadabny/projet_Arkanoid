#include "gameState.h"

int colorLetterToIndex(char colorLetter) {
    switch(colorLetter) {
        case 'o': return 0; // Orange
		case 'b': return 1; // light blue
		case 'g': return 2; // light green
		case 'n': return 3; // navy
		case 'f': return 4; // forest green
		case 'r': return 5; // red
		case 'c': return 6; // cyan
		case 'p': return 7; // pink
		case 'y': return 8; // yellow
		case 'd': return 9; // dark red
		case 't': return 10; // teal
        case 's': return 11; // silver
        case 'a': return 12; // dorée
        
        default: return -1; // Unknown color
    }
}

void loadLevel() {
    char levelPath[50];
    sprintf(levelPath, "../levels/level%d.txt", currentLevel);
    FILE* levelFile = fopen(levelPath, "r");
    if (!levelFile) {
        perror("Failed to open level file");
        exit(1);
    }

    char line[BRICKS_PER_ROW * 2 + 2]; // Assuming 2 characters per brick, +2 for potential newline and null terminator
    int row = 0;

    while (fgets(line, sizeof(line), levelFile) != NULL && row < BRICK_ROWS) {
        int col = 0;
        for (int i = 0; line[i] != '\0' && col < BRICKS_PER_ROW; i += 2) {
            // Skip newline characters
            if (line[i] == '\n' || line[i] == '\r') {
                continue;
            }

            char brickTypeChar = line[i];
            char colorChar = line[i + 1];

            // Determine the brick type and color
            switch (brickTypeChar) {
                case '1':
                    bricks[row][col].type = BRICK_NORMAL;
                    bricks[row][col].color = colorLetterToIndex(colorChar);
                    break;
                case '2':
                    bricks[row][col].type = BRICK_HARD;
                    break;
                case '3':
                    bricks[row][col].type = BRICK_INDESTRUCTIBLE;
                    break;
                default:
                    // Handle unexpected brickTypeChar if necessary
                    break;
            }

            col++;
        }
        row++;
    }

    fclose(levelFile);
}


void resetGameState() {
    // Reset the ball position, velocity, and any other relevant state for the new level
    ball.x = win_surf->w / 2;
    ball.y = win_surf->h - 50; // Example position, adjust as needed
    ball.vx = 1.0;
    ball.vy = -1.4;

    // Reset or clear other states as needed (e.g., paddle position, score, etc.)
    x_vault = (win_surf->w / 2) - (scrVaiss.w / 2); // Center the paddle
}

void loadNextLevel() {
	isGamePaused = true;
    currentLevel++;
    char levelPath[50];

    sprintf(levelPath, "../levels/level%d.txt", currentLevel);

    FILE* levelFile = fopen(levelPath, "r");
    if (levelFile == NULL) {
        printf("Congratulations! You've completed all available levels or an error occurred loading the next level.\n");
        exit(0); 
    }
        fclose(levelFile);

        // Load the level now that we know it exists
        loadLevel(levelPath);

        // Reset game state for the new level
        resetGameState();
		ball.vx *= 2; // Augmente la vitesse horizontale de 10%
        ball.vy *= 2;
    }