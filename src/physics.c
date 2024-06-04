#include "physics.h"
#include "gameState.h"
#include "score.h"
#include "powerup.h"

bool checkLevelCompletion() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICKS_PER_ROW; j++) {
            if (bricks[i][j].type != BRICK_INDESTRUCTIBLE && bricks[i][j].type != BRICK_NONE) {
                return false;
            }
        }
    }
    return true;
}

void handleCollisionWithBricks() {
    bool collisionDetected = false;
    int hitsRequiredForHardBrick = 2;

    if (currentLevel >= 9 && currentLevel <= 16) {
        hitsRequiredForHardBrick = 3;
    } else if (currentLevel >= 17 && currentLevel <= 24) {
        hitsRequiredForHardBrick = 4;
    } else if (currentLevel >= 25) {
        hitsRequiredForHardBrick = 5;
    }

    SDL_Rect ballRect = { (int)ball.x, (int)ball.y, 24, 24 };

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICKS_PER_ROW; j++) {
            Brick *brick = &bricks[i][j];
            if (brick->type == BRICK_NONE) continue;

            SDL_Rect brickRect = { j * BRICK_WIDTH, i * BRICK_HEIGHT + SCOREBOARD_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT };

            if (SDL_HasIntersection(&ballRect, &brickRect)) {
                collisionDetected = true;

                switch (brick->type) {
                    case BRICK_NORMAL:
                        brick->type = BRICK_NONE;
                        updateScore(50);
                        if ((rand() % 4) == 0) {
                            PowerUpType type = rand() % POWERUP_TOTAL;
                            spawnPowerUp(brickRect.x + BRICK_WIDTH / 2, brickRect.y + BRICK_HEIGHT / 2, type);
                        }
                        break;
                    case BRICK_HARD:
                        brick->shouldAnimate = true;
                        brick->animationFrame = 0;
                        brick->hitCount++;
                        if (brick->hitCount >= hitsRequiredForHardBrick) {
                            brick->type = BRICK_NONE;
                            updateScore(100 * currentLevel);
                        }
                        break;
                    case BRICK_INDESTRUCTIBLE:
                        brick->shouldAnimate = true;
                        brick->animationFrame = 0;
                        break;
                }

                if (ball.vy > 0) {
                    ball.y = brickRect.y - 24 - 1;
                } else {
                    ball.y = brickRect.y + BRICK_HEIGHT + 1;
                }

                ball.vy *= -1;

                goto collisionHandled;
            }
        }
    }

collisionHandled:
    if (collisionDetected) {
        if (checkLevelCompletion()) {
            loadNextLevel();
        }
    }
}
