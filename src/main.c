#include "globals.h"
#include "init.h"
#include "render.h"
#include "physics.h"
#include "gameState.h"
#include "score.h"




int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return 1;
    }

    init();
    initializeScore();
    loadLevel();
    
    
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_SPACE:
                        if (isGamePaused) {
                            isGamePaused = false; // Resume the game
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

        // Bounds checking for paddle movement
        if (x_vault < 0) {
            x_vault = 0; // Prevent moving beyond the left edge
        }
        if (x_vault > win_surf->w - scrVaiss.w) {
            x_vault = win_surf->w - scrVaiss.w; // Prevent moving beyond the right edge
        }

        handleCollisionWithBricks();
        draw();
        
        // SDL_Rect scoreArea = {100, 10, 10 * FONT_WIDTH, FONT_HEIGHT};  // Adjust the width as needed
        // SDL_FillRect(win_surf, &scoreArea, SDL_MapRGB(win_surf->format, 0, 0, 0));  // Assuming black is the background color
        // drawScore(win_surf, currentScore, 100, 10); // Draw current score at position (100,10)

        // scoreArea.x = win_surf->w - 100 - 10 * FONT_WIDTH;  // Adjust for the high score display
        // SDL_FillRect(win_surf, &scoreArea, SDL_MapRGB(win_surf->format, 0, 0, 0));  // Fill again for high score
        // drawScore(win_surf, highScore, win_surf->w - 100, 10); // Draw high score

        drawScoreboard(win_surf, currentScore, highScore);

        SDL_UpdateWindowSurface(pWindow);

        now = SDL_GetPerformanceCounter();
        delta_t = 1.0 / FPS - (double)(now - prev) / (double)SDL_GetPerformanceFrequency();
        if (delta_t > 0) {
            SDL_Delay((Uint32)(delta_t * 1000));
        }
        prev = SDL_GetPerformanceCounter();
    }

    

    SDL_Quit();
    return 0;
}
