#include "render.h"
#include "gameState.h"
//#include "score.h"



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
    
	{0, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT}
};

SDL_Rect srcRectsIndestructableBrick[] = {
    
	{0, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT}
};

SDL_Rect srcBackgrounds[] = {
    
    {0, 64*3, 48, 64}, 
	{0, 64*3, 48, 64},
	{64, 64*3, 48, 64},
	{64*2, 64*3, 48, 64},
	{64*3, 64*3, 48, 64},
	{64*4, 64*3, 48, 64},
    
};


// Rendering related functions
void draw()
{
    // Fill the background
    SDL_Rect srcBg = srcBackgrounds[currentLevel % (sizeof(srcBackgrounds) / sizeof(srcBackgrounds[0]))];
// Calculate how many times to repeat the background tile across the screen
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
    SDL_Rect dstBall = {ball.x, ball.y, 0, 0};
    SDL_BlitSurface(plancheSprites, &srcBall, win_surf, &dstBall);

    // Movement
    ball.x += ball.vx;
    ball.y += ball.vy;

    // Border collision
    if ((ball.x < 1) || (ball.x > (win_surf->w - 25)))
        ball.vx *= -1;
    if (ball.y < SCOREBOARD_HEIGHT)
    {
        ball.vy *= -1 ;
        ball.y = SCOREBOARD_HEIGHT;
        }
    else if (ball.y >= win_surf->h - scrVaiss.h - 25) // Adjusted to check for collision at paddle height
    {
        // Check if the ball is within the paddle's x-range
        if (ball.x >= x_vault && ball.x <= (x_vault + scrVaiss.w - 25)) // Assuming ball width is 25 pixels
        {
            // If the ball hits the paddle, invert the y-velocity
            ball.vy *= -1;
            ball.y = win_surf->h - scrVaiss.h - 25; // Adjust ball position to be exactly above the paddle
        }
        else
        {
            // Game over logic here. For simplicity, we just print "Game Over" and exit.
            printf("Game Over!\n");
            exit(0); // Exit the game
        }
    }

    // Paddle
    dest.x = x_vault;
    dest.y = win_surf->h - scrVaiss.h; // Position the paddle at the correct height
    SDL_BlitSurface(plancheSprites, &scrVaiss, win_surf, &dest);

}


void drawBricks() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICKS_PER_ROW; j++) {
            if (bricks[i][j].type != BRICK_NONE && bricks[i][j].color >= 0) {
                SDL_Rect brickRect = { j * BRICK_WIDTH, i * BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT };
                
                SDL_Rect srcRect = srcRectsNormalBrick[bricks[i][j].color];
                


                
                SDL_BlitSurface(brickSpriteSheet, &srcRect, win_surf, &brickRect);
            }
            // if (bricks[i][j].type != BRICK_NONE)
            // {
            //     if (bricks[i][j].type = BRICK_NORMAL && bricks[i][j].color >= 0)
            //     {
            //         SDL_Rect brickRect = { j * BRICK_WIDTH, i * BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT };
                
            //         SDL_Rect srcRect = srcRectsNormalBrick[bricks[i][j].color];

            //     }
            //     else if (bricks[i][j].type = BRICK_HARD)
            //     {
            //         SDL_Rect brickRect = { j * BRICK_WIDTH, i * BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT };
                
            //         SDL_Rect srcRect = srcRectsHardBrick[bricks[i][j].color];
            //     }
            //     else if (bricks[i][j].type = BRICK_INDESTRUCTIBLE)
            //     {
            //         SDL_Rect brickRect = { j * BRICK_WIDTH, i * BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT };
                
            //         SDL_Rect srcRect = srcRectsIndestructableBrick[bricks[i][j].color];
            //     }
                
            // }
            
        }
    }
}