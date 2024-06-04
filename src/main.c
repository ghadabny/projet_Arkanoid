/*#include "globals.h"
#include "init.h"
#include "render.h"
#include "physics.h"
#include "gameState.h"
#include "score.h"
#include "powerup.h"

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("SDL Initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    init();
    initializeScore();
    initializePowerUps();
    loadLevel();

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                printf("SDL_QUIT event received\n");
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        printf("Escape key pressed\n");
                        break;
                    case SDLK_SPACE:

                            if (isGamePaused) {
                            isGamePaused = false; // Resume the game
                        } else if (ballIsSticky && ball.vx == 0 && ball.vy == 0) {
                            releaseBall(); // Release the ball if it's sticky
                        } else if (ball.vx == 0 && ball.vy == 0) {
                            ball.vx = 1.0; // Set the initial ball velocity
                            ball.vy = 1.4;
                        }
                        
                        break;
                }
            }
        }

        const Uint8 *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT]) {
            x_vault -= 10;
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            x_vault += 10;
        }

        // Bounds checking for paddle movement
        if (x_vault < 0) {
            x_vault = 0; // Prevent moving beyond the left edge
        }
        if (x_vault > win_surf->w - scrVaiss.w) {
            x_vault = win_surf->w - scrVaiss.w; // Prevent moving beyond the right edge
        }

        if (ball.vx == 0 && ball.vy == 0) {
            ball.x = x_vault + (scrVaiss.w / 2) - 12; // Ensure the ball stays on the paddle while waiting for launch
            //printf("Ball on paddle. Ball position: (%f, %f)\n", ball.x, ball.y);
        }

        if (!isGamePaused) {
            updateAnimations();
            handleCollisionWithBricks();
            updatePowerUps();
            handlePowerUpCollection(); // Call the power-up collection handler

            SDL_FillRect(win_surf, NULL, SDL_MapRGB(win_surf->format, 0, 0, 0));

            draw();
            renderPowerUps();
            drawScoreboard(win_surf, currentScore, highScore);

            SDL_UpdateWindowSurface(pWindow);

            // Check if the ball has fallen off the paddle
            if (ball.y > win_surf->h) {
               // printf("Ball fell off the screen. Ball position: (%f, %f)\n", ball.x, ball.y);
                handleBallOutOfBounds(); // Handle ball out of bounds
            } else {
                // Print the ball's position for further debugging
               // printf("Ball position during game loop: (%f, %f)\n", ball.x, ball.y);
            }

            if (playerLives <= 0) {
                printf("Game Over! Quitting game loop.\n");
                quit = true;
            }
        }

        now = SDL_GetPerformanceCounter();
        delta_t = 1.0 / FPS - (double)(now - prev) / (double)SDL_GetPerformanceFrequency();
        if (delta_t > 0) {
            SDL_Delay((Uint32)(delta_t * 1000));
        }
        prev = SDL_GetPerformanceCounter();
    }

    printf("Exiting game. Cleaning up.\n");
    SDL_Quit(); // Quit SDL only if the game is completely done
    return 0;
}
*/

#include "globals.h"
#include "init.h"
#include "render.h"
#include "physics.h"
#include "gameState.h"
#include "score.h"
#include "powerup.h"
#include "menu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("SDL Initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Display the main menu
    SDL_Window* window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        return 1;
    }
    
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    bool startGame = afficher_menu(window, surface);
    if (!startGame) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    // Game initialization
    init();
    initializeScore();
    initializePowerUps();
    loadLevel();

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                printf("SDL_QUIT event received\n");
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        printf("Escape key pressed\n");
                        break;
                    case SDLK_SPACE:
                        if (isGamePaused) {
                            isGamePaused = false; // Resume the game
                            printf("Game resumed\n");
                        } else if (ballIsSticky && ball.vx == 0 && ball.vy == 0) {
                            releaseBall(); // Release the ball if it's sticky
                        } else if (ball.vx == 0 && ball.vy == 0) {
                            ball.vx = 1.0; // Set the initial ball velocity
                            ball.vy = 1.4;
                        }
                        break;
                }
            }
        }

        if (isGamePaused) {
            // Skip the rest of the loop if the game is paused
            continue;
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT]) {
            x_vault -= 10;
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            x_vault += 10;
        }

        // Paddle movement bounds checking
        if (x_vault < 0) {
            x_vault = 0; // Prevent moving beyond the left edge
        }
        if (x_vault > win_surf->w - scrVaiss.w) {
            x_vault = win_surf->w - scrVaiss.w; // Prevent moving beyond the right edge
        }

        if (ball.vx == 0 && ball.vy == 0) {
            ball.x = x_vault + (scrVaiss.w / 2) - 12; // Ensure the ball stays on the paddle while waiting for launch
        }

        updateAnimations();
        handleCollisionWithBricks();
        updatePowerUps();
        handlePowerUpCollection(); // Call the power-up collection handler

        SDL_FillRect(win_surf, NULL, SDL_MapRGB(win_surf->format, 0, 0, 0));
       
        draw();
        renderPowerUps();
        drawScoreboard(win_surf, currentScore, highScore);

        SDL_UpdateWindowSurface(pWindow);

        // Check if the ball has fallen off the paddle
        if (ball.y > win_surf->h) {
            handleBallOutOfBounds(); // Handle ball out of bounds
        }

        if (playerLives <= 0) {
            printf("Game Over! Quitting game loop.\n");
            quit = true;
        }

        now = SDL_GetPerformanceCounter();
        delta_t = 1.0 / FPS - (double)(now - prev) / (double)SDL_GetPerformanceFrequency();
        if (delta_t > 0) {
            SDL_Delay((Uint32)(delta_t * 1000));
        }
        prev = SDL_GetPerformanceCounter();
    }

    printf("Exiting game. Cleaning up.\n");
    SDL_DestroyWindow(window);
    SDL_Quit(); // Quit SDL only if the game is completely done
    return 0;
}
