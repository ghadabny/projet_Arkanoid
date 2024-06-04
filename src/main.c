#include "globals.h"
#include "init.h"
#include "render.h"
#include "physics.h"
#include "gameState.h"
#include "score.h"
#include "powerup.h"
#include "menu.h" // Ajout de l'inclusion de menu.h

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return 1;
    }

    // Afficher le menu principal
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

    // Initialisation du jeu
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
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_SPACE:
                        if (isGamePaused) {
                            isGamePaused = false; // Reprendre le jeu
                        }
                        break;
                }
            }
        }

        if (isGamePaused) {
            // Passer le reste de la boucle si le jeu est en pause
            continue;
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT]) {
            x_vault -= 10;
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            x_vault += 10;
        }

        updateAnimations();
        handleCollisionWithBricks();
        updatePowerUps();

        // Vérification des limites pour le mouvement de la raquette
        if (x_vault < 0) {
            x_vault = 0; // Empêcher de dépasser le bord gauche
        }
        if (x_vault > win_surf->w - scrVaiss.w) {
            x_vault = win_surf->w - scrVaiss.w; // Empêcher de dépasser le bord droit
        }

        SDL_FillRect(win_surf, NULL, SDL_MapRGB(win_surf->format, 0, 0, 0));
       
        draw();
        renderPowerUps();
        drawScoreboard(win_surf, currentScore, highScore);

        SDL_UpdateWindowSurface(pWindow);

        now = SDL_GetPerformanceCounter();
        delta_t = 1.0 / FPS - (double)(now - prev) / (double)SDL_GetPerformanceFrequency();
        if (delta_t > 0) {
            SDL_Delay((Uint32)(delta_t * 1000));
        }
        prev = SDL_GetPerformanceCounter();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
