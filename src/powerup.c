#include "powerup.h"

PowerUp powerUps[MAX_POWERUPS]; // Definition
int activePowerUps = 0;

SDL_Rect srcRectsSlow[]={
    {BRICK_WIDTH *8 , 0, BRICK_WIDTH, BRICK_HEIGHT}, 
	{BRICK_WIDTH *9 , 0, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH *10 , 0, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH *11 , 0, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH *12 , 0, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH *13 , 0, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH *14 , 0,BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH *15 , 0, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH *16 , 0, BRICK_WIDTH, BRICK_HEIGHT}
    };

SDL_Rect srcRectsCatch[]={
     {BRICK_WIDTH *8 , BRICK_HEIGHT,  BRICK_WIDTH, BRICK_HEIGHT}, 
	{BRICK_WIDTH *9 , BRICK_HEIGHT,  BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH *10 , BRICK_HEIGHT,  BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH *11 , BRICK_HEIGHT,  BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH *12 , BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH *13, BRICK_HEIGHT,  BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH *14, BRICK_HEIGHT,  BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH *15, BRICK_HEIGHT,  BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH *16, BRICK_HEIGHT ,  BRICK_WIDTH, BRICK_HEIGHT}
    };


SDL_Rect srcRectsLaser[]={
     {BRICK_WIDTH *8, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT}, 
	{BRICK_WIDTH *9, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*10, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*11, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*12, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*13, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*14, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*15, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*16, BRICK_HEIGHT*2, BRICK_WIDTH, BRICK_HEIGHT}
    };



SDL_Rect srcRectsExpand[]={
     {BRICK_WIDTH *8, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT}, 
	{BRICK_WIDTH *9, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*10, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*11, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*12, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*13, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*14, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*15, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*16, BRICK_HEIGHT*3, BRICK_WIDTH, BRICK_HEIGHT}
    };

SDL_Rect srcRectsDivide[]={
      {BRICK_WIDTH *8, BRICK_HEIGHT*4, BRICK_WIDTH, BRICK_HEIGHT}, 
	{BRICK_WIDTH *9, BRICK_HEIGHT*4, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*10, BRICK_HEIGHT*4, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*11, BRICK_HEIGHT*4, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*12, BRICK_HEIGHT*4, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*13, BRICK_HEIGHT*4, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*14, BRICK_HEIGHT*4, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*15, BRICK_HEIGHT*4, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*16, BRICK_HEIGHT*4, BRICK_WIDTH, BRICK_HEIGHT}
    };

SDL_Rect srcRectsBreak[]={
        {BRICK_WIDTH *8, BRICK_HEIGHT*5, BRICK_WIDTH, BRICK_HEIGHT}, 
	{BRICK_WIDTH *9, BRICK_HEIGHT*5, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*10, BRICK_HEIGHT*5, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*11, BRICK_HEIGHT*5, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*12, BRICK_HEIGHT*5, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*13, BRICK_HEIGHT*5, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*14, BRICK_HEIGHT*5, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*15, BRICK_HEIGHT*5, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*16, BRICK_HEIGHT*5, BRICK_WIDTH, BRICK_HEIGHT}
    };

extern SDL_Rect srcRectsPlayer[]={
     {BRICK_WIDTH *8, BRICK_HEIGHT*6, BRICK_WIDTH, BRICK_HEIGHT}, 
	{BRICK_WIDTH *9, BRICK_HEIGHT*6, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*10, BRICK_HEIGHT*6, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*11, BRICK_HEIGHT*6, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*12, BRICK_HEIGHT*6, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*13, BRICK_HEIGHT*6, BRICK_WIDTH, BRICK_HEIGHT},
    {BRICK_WIDTH*14, BRICK_HEIGHT*6, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*15, BRICK_HEIGHT*6, BRICK_WIDTH, BRICK_HEIGHT},
	{BRICK_WIDTH*16, BRICK_HEIGHT*6, BRICK_WIDTH, BRICK_HEIGHT}
    };

 

#include "powerup.h"
#include <SDL.h>

extern PowerUp powerUps[10]; // Example array, adjust according to your game's needs
extern int activePowerUps;   // Track the number of active power-ups


void spawnPowerUp(double x, double y, PowerUpType type) {
    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (!powerUps[i].isActive) {
            powerUps[i].x = x;
            powerUps[i].y = y;
            powerUps[i].vy = 1.0;
            powerUps[i].type = type;
            powerUps[i].isActive = true;
            powerUps[i].animationFrame = 0; // Ensure animation frame starts at 0
            activePowerUps++;
            return; // Exit after spawning
        }
    }
}

void initializePowerUps() {
    for (int i = 0; i < MAX_POWERUPS; i++) {
        powerUps[i].x = 0;
        powerUps[i].y = 0;
        powerUps[i].vy = 0;
        powerUps[i].type = POWERUP_TOTAL; // Indicates an inactive or undefined power-up
        powerUps[i].isActive = false;
        powerUps[i].animationFrame = 0;
    }
}

SDL_Rect* getCurrentPowerUpSprite(PowerUp* powerUp) {
    switch(powerUp->type) {
        case POWERUP_SLOW:
            return &srcRectsSlow[powerUp->animationFrame % 9];
        case POWERUP_CATCH:
            return &srcRectsCatch[powerUp->animationFrame % 9];
       /* case POWERUP_LASER:
            return &srcRectsLaser[powerUp->animationFrame % 9];
        case POWERUP_EXPAND:
            return &srcRectsExpand[powerUp->animationFrame % 9];
        case POWERUP_DIVIDE:
            return &srcRectsDivide[powerUp->animationFrame % 9];
        */case POWERUP_BREAK:
            return &srcRectsBreak[powerUp->animationFrame % 9];
        case POWERUP_PLAYER:
            return &srcRectsPlayer[powerUp->animationFrame % 9];
        default:
            return NULL; // Consider logging or handling this unexpected case
    }

}


void updatePowerUps() {
    // Assume MAX_POWERUPS and powerUps[] array or equivalent exist
    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (powerUps[i].isActive) {
            // Update position based on vertical speed
            powerUps[i].y += powerUps[i].vy;

            // Cycle through animation frames
            powerUps[i].animationFrame = (powerUps[i].animationFrame + 1) % 9; // Assuming 9 frames per power-up animation

            // Check if the power-up has moved off-screen
            // win_surf->h gives the height of the window surface, used for boundary checking
            if (powerUps[i].y > win_surf->h) {
                powerUps[i].isActive = false; // Deactivate power-up
            }
        }

        //printf("Updating power-up %d position to y: %f\n", i, powerUps[i].y);
    }
}


// Adjusted to use global variables directly

void renderPowerUps() {
    SDL_Surface* surface = win_surf; // Directly use the global surface
    SDL_Surface* spriteSheet = brickSpriteSheet; // Directly use the global sprite sheet

    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (powerUps[i].isActive) {
            SDL_Rect* currentSprite = getCurrentPowerUpSprite(&powerUps[i]);
            if (currentSprite) {
                SDL_Rect destRect = { (int)powerUps[i].x, (int)powerUps[i].y, POWERUP_WIDTH, POWERUP_HEIGHT };
                SDL_BlitSurface(spriteSheet, currentSprite, surface, &destRect);
            }
        }
        //printf("Rendering power-up at x: %d, y: %d\n", powerUps[i].x, powerUps[i].y);
    }
}


// This would be part of your game loop or a specific collision detection function
void handlePowerUpCollection() {
    SDL_Rect paddleRect = {x_vault, win_surf->h - scrVaiss.h, scrVaiss.w, scrVaiss.h}; // Assuming paddle dimensions are in scrVaiss
    for (int i = 0; i < MAX_POWERUPS; i++) {
        if (powerUps[i].isActive) {
            SDL_Rect powerUpRect = {powerUps[i].x, powerUps[i].y, POWERUP_WIDTH, POWERUP_HEIGHT}; // Define POWERUP_WIDTH and POWERUP_HEIGHT as needed
            if (SDL_HasIntersection(&paddleRect, &powerUpRect)) {
                // Power-up collected, apply effect based on type
                powerUps[i].isActive = false;
                activePowerUps--;

                switch (powerUps[i].type) {
                    case POWERUP_PLAYER:
                        addExtraLife();
                        break;
                    case POWERUP_CATCH:
                        activateCatch();
                        break;
                    case POWERUP_BREAK:
                        breakBricks();
                        break;
                    case POWERUP_SLOW:
                        slowBall();
                        break;
                }
            }
        }
    }
}



void clearPowerUps() {
    for (int i = 0; i < MAX_POWERUPS; i++) {
        powerUps[i].isActive = false;
    }
    activePowerUps = 0;
}



void addExtraLife() {
    playerLives++;
    printf("Extra life added! Lives remaining: %d\n", playerLives);
}


void activateCatch() {
    ballIsSticky = true;
}

void releaseBall() {
    if (ballIsSticky && ball.vx == 0 && ball.vy == 0) {
        ball.vx = 1.0; // Set the initial ball velocity
        ball.vy = 1.4;
        ballIsSticky = false; // Release the ball from being sticky
    }
} 

void breakBricks() {
    loadNextLevel();

}

void slowBall() {
    ball.vx *= 0.5; // Slow down the ball by 50%
    ball.vy *= 0.5;
}






