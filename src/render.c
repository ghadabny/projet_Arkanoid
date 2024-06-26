#include "render.h"
#include "gameState.h"
#include "physics.h"

SDL_Rect srcRectsNormalBrick[] = {
    {BRICK_WIDTH, 0, BRICK_WIDTH, BRICK_HEIGHT}, 
    {BRICK_WIDTH*2, 0, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*3, 0, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*4, 0, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*5, 0, BRICK_WIDTH, BRICK_HEIGHT},
    {0, BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH, BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*2, BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*3, BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*4, BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*5, BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT}
};

SDL_Rect srcRectsHardBrick[] = {
    {0, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT}, 
    {BRICK_WIDTH, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*2, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*3, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*4, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*5, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT}
};

SDL_Rect srcRectsIndestructableBrick[] = {
    {0, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT}, 
    {BRICK_WIDTH, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*2, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*3, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*4, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*5, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT}
};

SDL_Rect srcBackgrounds[] = {
    {0, 64*3, 48, 64}, 
    {0, 64*3, 48, 64},
    {64, 64*3, 48, 64},
    {64*2, 64*3, 48, 64},
    {64*3, 64*3, 48, 64},
    {64*4, 64*3, 48, 64}
};

void draw() {
    // Fill the background
    SDL_Rect srcBg = srcBackgrounds[currentLevel % (sizeof(srcBackgrounds) / sizeof(srcBackgrounds[0]))];
    int bgRepeatsX = win_surf->w / srcBg.w + (win_surf->w % srcBg.w != 0);
    int bgRepeatsY = win_surf->h / srcBg.h + (win_surf->h % srcBg.h != 0);

    SDL_Rect dest;
    for (int j = 0; j < bgRepeatsY; j++) {
        for (int i = 0; i < bgRepeatsX; i++) {
            dest.x = i * srcBg.w;
            dest.y = j * srcBg.h;
            SDL_BlitSurface(brickSpriteSheet, &srcBg, win_surf, &dest);
        }
    }

    // Draw bricks
    drawBricks(); // This call draws the bricks over the background

    // Display ball
    SDL_Rect dstBall = { (int)ball.x, (int)ball.y, 24, 24 };
    SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);

    // Handle ball movement and collision
    if (!ballIsSticky || (ball.vx != 0 && ball.vy != 0)) {
        ball.x += ball.vx;
        ball.y += ball.vy;

        // Border collision
        if ((ball.x < 1) || (ball.x > (win_surf->w - 25)))
            ball.vx *= -1;
        if (ball.y < SCOREBOARD_HEIGHT) {
            ball.vy *= -1;
            ball.y = SCOREBOARD_HEIGHT;
        } else if (ball.y >= win_surf->h - scrVaiss.h - 25) { // Adjusted to check for collision at paddle height
            // Check if the ball is within the paddle's x-range
            if (ball.x >= x_vault && ball.x <= (x_vault + scrVaiss.w - 25)) { // Assuming ball width is 25 pixels
                if (ballIsSticky) {
                    ball.vx = 0;
                    ball.vy = 0;
                    ball.y = win_surf->h - scrVaiss.h - 25; // Adjust ball position to be exactly above the paddle
                } else {
                    ball.vy *= -1;
                    ball.y = win_surf->h - scrVaiss.h - 25; // Adjust ball position to be exactly above the paddle
                }
            } else {
                // Handle the ball going out of bounds without exiting the game
                handleBallOutOfBounds();
            }
        }
    }

    // Paddle
    dest.x = x_vault;
    dest.y = win_surf->h - scrVaiss.h; // Position the paddle at the correct height
    SDL_BlitSurface(plancheSprites, &scrVaiss, win_surf, &dest);
}

// Rest of your functions...

void updateAnimations() {
    const int FRAME_DELAY = 3; // Number of frames to wait before switching to the next animation frame

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICKS_PER_ROW; j++) {
            Brick *brick = &bricks[i][j];
            if ((brick->type == BRICK_HARD || brick->type == BRICK_INDESTRUCTIBLE) && brick->shouldAnimate) {
                brick->animationCounter++;
                
                if (brick->animationCounter >= FRAME_DELAY) {
                    // Reset counter
                    brick->animationCounter = 0;
                    
                    // Move to the next frame
                    brick->animationFrame++;
                    
                    // Check if the animation sequence is complete
                    if (brick->animationFrame >= (brick->type == BRICK_HARD ? sizeof(srcRectsHardBrick) : sizeof(srcRectsIndestructableBrick)) / sizeof(SDL_Rect)) {
                        brick->animationFrame = 0; // Optionally loop or stop animating
                        brick->shouldAnimate = false; // Consider stopping the animation
                    }
                }
            }
        }
    }
}

void drawBricks() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICKS_PER_ROW; j++) {
            Brick *brick = &bricks[i][j];
            if (brick->type == BRICK_NONE) continue;

            SDL_Rect brickRect = { j * BRICK_WIDTH, i * BRICK_HEIGHT + SCOREBOARD_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT };
            SDL_Rect srcRect;

            switch (brick->type) {
                case BRICK_NORMAL:
                    srcRect = srcRectsNormalBrick[brick->color];
                    break;
                case BRICK_HARD:
                    srcRect = srcRectsHardBrick[brick->animationFrame % 6]; // Use animation frame without updating it here
                    break;
                case BRICK_INDESTRUCTIBLE:
                    srcRect = srcRectsIndestructableBrick[brick->animationFrame % 6];
                    break;
            }

            SDL_BlitSurface(brickSpriteSheet, &srcRect, win_surf, &brickRect);
        }
    }
}
