#include "physics.h"
#include "gameState.h"
#include "score.h"

// void handleCollisionWithBricks() {
//     bool collisionDetected = false;
//     int hitsRequiredForHardBrick = 2; // Default for rounds 1 to 8

//     // Determine the required hits based on the current level
//     if (currentLevel >= 9 && currentLevel <= 16) {
//         hitsRequiredForHardBrick = 3;
//     } else if (currentLevel >= 17 && currentLevel <= 24) {
//         hitsRequiredForHardBrick = 4;
//     } else if (currentLevel >= 25) {
//         hitsRequiredForHardBrick = 5;
//     }

//     // Calculate the ball's bounding box
//     SDL_Rect ballRect = { (int)ball.x, (int)ball.y, 24, 24 };

//     for (int i = 0; i < BRICK_ROWS; i++) {
//         for (int j = 0; j < BRICKS_PER_ROW; j++) {
//             if (bricks[i][j].type != BRICK_NONE) {
//                 // Calculate the brick's bounding box
//                 SDL_Rect brickRect = { j * BRICK_WIDTH, i * BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT };

//                 // Check if the ball collides with the brick
//                 if (SDL_HasIntersection(&ballRect, &brickRect)) {
//                     collisionDetected = true;

//                     // Handle collision based on the brick type
//                     switch (bricks[i][j].type) {
//                         case BRICK_NORMAL:
//                             bricks[i][j].type = BRICK_NONE;
//                             updateScore(50); // Score for a normal brick
//                             break;
//                         case BRICK_HARD:
//                             bricks[i][j].hitCount++;
//                             if (bricks[i][j].hitCount >= hitsRequiredForHardBrick) {
//                                 bricks[i][j].type = BRICK_NONE;
//                                 updateScore(100);  // Score for a hard brick
//                             }
//                             break;
//                         // Handle any other brick types if necessary
//                     }

//                     // Bounce the ball off the brick
//                     ball.vy = -ball.vy;

//                     // Only one collision is handled per frame
//                     goto collisionHandled;
//                 }
//             }
//         }
//     }

// collisionHandled:
//     if (collisionDetected) {
//         // Check if all bricks have been cleared
//         bool levelCleared = true;
//         for (int i = 0; i < BRICK_ROWS; i++) {
//             for (int j = 0; j < BRICKS_PER_ROW; j++) {
//                 if (bricks[i][j].type != BRICK_NONE) {
//                     levelCleared = false;
//                     break;
//                 }
//             }
//             if (!levelCleared) break;
//         }

//         //Load the next level if all bricks are cleared
//         if (levelCleared) {
//             loadNextLevel();
//         }
//     }
// }

#include "physics.h"
#include "gameState.h"
#include "score.h"

void handleCollisionWithBricks() {
    bool collisionDetected = false;
    int hitsRequiredForHardBrick = 2; // Default for rounds 1 to 8

    if (currentLevel >= 9 && currentLevel <= 16) {
        hitsRequiredForHardBrick = 3;
    } else if (currentLevel >= 17 && currentLevel <= 24) {
        hitsRequiredForHardBrick = 4;
    } else if (currentLevel >= 25) {
        hitsRequiredForHardBrick = 5;
    }

    SDL_Rect ballRect = { (int)ball.x, (int)ball.y, 24, 24 }; // Ensure BALL_WIDTH and BALL_HEIGHT are correctly defined

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICKS_PER_ROW; j++) {
            Brick *brick = &bricks[i][j]; // Pointer to the current brick
            if (brick->type == BRICK_NONE) continue; // Skip if brick is already destroyed

            SDL_Rect brickRect = { j * BRICK_WIDTH, i * BRICK_HEIGHT + SCOREBOARD_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT };

            if (SDL_HasIntersection(&ballRect, &brickRect)) {
                collisionDetected = true;

                switch (brick->type) {
                    case BRICK_NORMAL:
                        brick->type = BRICK_NONE; // Destroy the brick immediately
                        updateScore(50); // Update score for destroying a normal brick
                        break;
                    case BRICK_HARD:
                        brick->shouldAnimate = true;
                        brick->animationFrame = 0;
                        brick->hitCount++; // Increment hit count for hard bricks
                        if (brick->hitCount >= hitsRequiredForHardBrick) {
                            brick->type = BRICK_NONE;
                             // Destroy the hard brick once hit count exceeds required hits
                            updateScore(100*currentLevel);
                             // Update score for destroying a hard brick
                        }
                        break;
                    case BRICK_INDESTRUCTIBLE:
                        brick->shouldAnimate = true;
                        brick->animationFrame = 0;

                        break;
                    // Handle other brick types if necessary
                }

                // Adjust ball's position slightly before bouncing to prevent sticking to the brick
                if (ball.vy > 0) {
                    ball.y = brickRect.y - 24 - 1; // Adjust for ball height and ensure it's just above the brick
                } else {
                    ball.y = brickRect.y + BRICK_HEIGHT + 1; // Place it just below the brick
                }

                ball.vy *= -1; // Invert ball's vertical velocity to bounce back

                // After handling the collision, exit the loop to avoid multiple bounces in one frame
                goto collisionHandled;
            }
        }
    }

collisionHandled:
    if (collisionDetected) {
        // Check if all bricks have been cleared
        bool levelCleared = true;
        for (int i = 0; i < BRICK_ROWS; i++) {
            for (int j = 0; j < BRICKS_PER_ROW; j++) {
                if (bricks[i][j].type != BRICK_NONE) {
                    levelCleared = false;
                    break;
                }
            }
            if (!levelCleared) break;
        }

        //Load the next level if all bricks are cleared
        if (levelCleared) {
            loadNextLevel();
        }
    }
}

