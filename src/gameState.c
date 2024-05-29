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
    // Initialize all bricks to none
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICKS_PER_ROW; j++) {
            bricks[i][j].type = BRICK_NONE;
            bricks[i][j].color = 0; // Default color index, adjust as necessary
        }
    }

    char levelPath[50];
    sprintf(levelPath, "../levels/level%d.txt", currentLevel);
    FILE* levelFile = fopen(levelPath, "r");
    if (!levelFile) {
        perror("Failed to open level file");
        exit(1);
    }

    char line[BRICKS_PER_ROW * 2 + 2]; // +2 for newline and null terminator
    int row = 0;

    while (fgets(line, sizeof(line), levelFile) != NULL && row < BRICK_ROWS) {
        printf("Read line: %s\n", line);  // Print each line read from the file
        int col = 0;
        for (int i = 0; line[i] != '\0' && col < BRICKS_PER_ROW; i++) {
            if (line[i] == '\n' || line[i] == '\r' || line[i] == ' ') continue;

            char brickTypeChar = line[i];
            char colorChar = (brickTypeChar == '1') ? line[i + 1] : '\0'; // Only read colorChar for normal bricks

            printf("Read brick type: %c, color: %c at row %d, col %d\n", brickTypeChar, colorChar, row, col);  // Print each character read

            if (brickTypeChar < '0' || brickTypeChar > '3') {
                fprintf(stderr, "Unexpected brick type '%c' at row %d, col %d\n", brickTypeChar, row, col);
                continue;
            }

            if (brickTypeChar == '1' && colorLetterToIndex(colorChar) == -1) {
                fprintf(stderr, "Unexpected color '%c' at row %d, col %d\n", colorChar, row, col);
                continue;
            }

            switch (brickTypeChar) {
                case '0':
                    // Empty space, skip processing
                    col++;
                    continue;
                case '1':
                    bricks[row][col].type = BRICK_NORMAL;
                    bricks[row][col].color = colorLetterToIndex(colorChar);
                    i++; // Increment to skip colorChar for normal bricks
                    break;
                case '2':
                    bricks[row][col].type = BRICK_HARD;
                    bricks[row][col].color = 0; // Assign a default color for hard bricks
                    break;
                case '3':
                    bricks[row][col].type = BRICK_INDESTRUCTIBLE;
                    bricks[row][col].color = 0; // Assign a default color for indestructible bricks
                    break;
                default:
                    fprintf(stderr, "Unexpected brick type '%c' at row %d, col %d\n", brickTypeChar, row, col);
                    continue;
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