// #include "laser.h"
// #include "powerup.h"

// srcRectsLaserBeem[]={
//     {0,BRICK_HEIGHT*5,BRICK_WIDTH/2,BRICK_HEIGHT},
//     {0,BRICK_HEIGHT*6,BRICK_WIDTH/2,BRICK_HEIGHT/5},
//     {0,BRICK_HEIGHT*6+BRICK_HEIGHT/5,BRICK_WIDTH/2,BRICK_HEIGHT/5},
//     {0,BRICK_HEIGHT*6+2*BRICK_HEIGHT/5,BRICK_WIDTH/2,BRICK_HEIGHT/4}
//     };

    

// Laser lasers[MAX_LASERS];


// void activateLaserPowerUp(void) {
//     // Activate the laser power-up, make lasers ready to shoot
//     for (int i = 0; i < MAX_LASERS; ++i) {
//         lasers[i].active = false;
//         lasers[i].frame = 0;
//         lasers[i].frameCount = sizeof(srcRectsLaserBeem) / sizeof(SDL_Rect);
//         lasers[i].spriteFrames = srcRectsLaserBeem;
//     }
//     laserActive = true; // Assuming laserActive is a global flag indicating laser power-up state
// }

// void updateLasers(void) {
//     for (int i = 0; i < MAX_LASERS; ++i) {
//         if (lasers[i].active) {
//             lasers[i].y -= 5; // Move lasers up. Adjust speed as necessary.
//             if (lasers[i].y < 0 || laserHitsBrick(&lasers[i])) { // laserHitsBrick checks for collisions
//                 lasers[i].active = false;
//             }
//         }
//     }
// }

// void drawLasers(SDL_Surface* surface) {
//     SDL_Rect srcRect;
//     SDL_Rect destRect;
//     for (int i = 0; i < MAX_LASERS; ++i) {
//         if (lasers[i].active) {
//             // Set up source rectangle from the sprite frames
//             srcRect = srcRectsLaserBeem[lasers[i].frame];
//             // Set up destination rectangle
//             destRect.x = (int)lasers[i].x;
//             destRect.y = (int)lasers[i].y;
//             destRect.w = srcRect.w;
//             destRect.h = srcRect.h;
//             // Draw the laser
//             SDL_BlitSurface(plancheSprites, &srcRect, surface, &destRect);
//         }
//     }
// }

// void handleInput() {
//     const Uint8* keys = SDL_GetKeyboardState(NULL);
//     if (keys[SDL_SCANCODE_SPACE] && laserActive) {
//         SDL_Rect paddleRect = {x_vault, win_surf->h - scrVaiss.h, scrVaiss.w, scrVaiss.h}; // You need to replace these with the actual values for your paddle
//         shootLaserFromPaddle(paddleRect);
//     }
// }

// void deactivateLaserPowerUp(void) {
//     // Deactivate all lasers
//     for (int i = 0; i < MAX_LASERS; ++i) {
//         lasers[i].active = false;
//     }
//     laserActive = false;
// }

// void shootLaserFromPaddle(SDL_Rect paddleRect) {
//     for (int i = 0; i < MAX_LASERS; ++i) {
//         if (!lasers[i].active) {
//             lasers[i].x = paddleRect.x + paddleRect.w / 2; // Center on the paddle
//             lasers[i].y = paddleRect.y; // Start at the top of the paddle
//             lasers[i].active = true; // Activate the laser
//             lasers[i].frame = 0; // Start animation from the first frame
//             break; // Shoot one laser at a time
//         }
//     }
// }