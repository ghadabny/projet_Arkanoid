#include "menu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

bool afficher_menu(SDL_Window* window, SDL_Surface* surface) {
    SDL_Color blue = {0, 0, 255, 255}; // Couleur bleue pour le titre
    SDL_Color white = {255, 255, 255, 255}; // Couleur blanche pour les boutons "Jouer" et "Quitter"
    if (TTF_Init() == -1) {
        printf("Failed to initialize TTF: %s\n", TTF_GetError());
        return false;
    }

    TTF_Font* titleFont = TTF_OpenFont("font/LiberationSans-Regular.ttf", 80); // Augmenter la taille de la police pour le titre
    TTF_Font* buttonFont = TTF_OpenFont("font/LiberationSans-Regular.ttf", 40);
    if (!titleFont || !buttonFont) {
        printf("Failed to open font: %s\n", TTF_GetError());
        TTF_Quit();
        return false;
    }

    // Obtenez les dimensions de la fenêtre
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Calculer la position du titre "Arkanoid" au centre de la fenêtre
    int titleWidth, titleHeight;
    TTF_SizeText(titleFont, "Arkanoid", &titleWidth, &titleHeight);
    int titleX = (windowWidth - titleWidth) / 2;
    int titleY = windowHeight / 4;

    // Créer la surface de texte pour le titre "Arkanoid"
    SDL_Surface* titleSurface = TTF_RenderText_Solid(titleFont, "Arkanoid", blue); // Utiliser la couleur bleue
    if (!titleSurface) {
        printf("Failed to render title text: %s\n", TTF_GetError());
        TTF_CloseFont(titleFont);
        TTF_CloseFont(buttonFont);
        TTF_Quit();
        return false;
    }

    // Calculer la position des boutons "Jouer" et "Quitter" sur la même ligne
    int buttonWidth = 200;
    int buttonHeight = 50;
    int buttonSpacing = 20;
    int totalButtonWidth = 2 * buttonWidth + buttonSpacing;
    int startX = (windowWidth - totalButtonWidth) / 2 + 50; // Décalage de 50 pixels vers la droite
    int startY = titleY + titleHeight + 100; // Ajoutez une marge de 100 pixels sous le titre pour déplacer les boutons plus bas

    // Créer les surfaces de texte pour les boutons "Jouer" et "Quitter"
    SDL_Surface* jouerSurface = TTF_RenderText_Solid(buttonFont, "Jouer", white); // Utiliser la couleur blanche
    SDL_Surface* quitterSurface = TTF_RenderText_Solid(buttonFont, "Quitter", white); // Utiliser la couleur blanche
    if (!jouerSurface || !quitterSurface) {
        printf("Failed to render button text: %s\n", TTF_GetError());
        SDL_FreeSurface(titleSurface);
        TTF_CloseFont(titleFont);
        TTF_CloseFont(buttonFont);
        TTF_Quit();
        return false;
    }

    // Calculer les rectangles des boutons "Jouer" et "Quitter"
    SDL_Rect jouerRect = {startX, startY, jouerSurface->w, jouerSurface->h};
    SDL_Rect quitterRect = {startX + buttonWidth + buttonSpacing, startY, quitterSurface->w, quitterSurface->h};

    // Dessiner le titre "Arkanoid" au centre de la fenêtre
    SDL_BlitSurface(titleSurface, NULL, surface, &(SDL_Rect){titleX, titleY, titleWidth, titleHeight});

    // Dessiner les surfaces de texte des boutons "Jouer" et "Quitter"
    SDL_BlitSurface(jouerSurface, NULL, surface, &jouerRect);
    SDL_BlitSurface(quitterSurface, NULL, surface, &quitterRect);
    SDL_UpdateWindowSurface(window);

    // Libérer la mémoire et fermer la bibliothèque SDL_ttf
    SDL_FreeSurface(titleSurface);
    SDL_FreeSurface(jouerSurface);
    SDL_FreeSurface(quitterSurface);
    TTF_CloseFont(titleFont);
    TTF_CloseFont(buttonFont);
    TTF_Quit();

    // Attendre les événements de la fenêtre
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                SDL_DestroyWindow(window);
                SDL_Quit();
                return false;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Vérifiez si le clic est dans la zone "Jouer"
                    if (event.button.x >= jouerRect.x && event.button.x <= jouerRect.x + jouerRect.w &&
                        event.button.y >= jouerRect.y && event.button.y <= jouerRect.y + jouerRect.h) {
                        SDL_DestroyWindow(window); // Ferme la fenêtre du menu
                        return true; // Indique que le joueur a cliqué sur "Jouer"
                    }
                    // Vérifiez si le clic est dans la zone "Quitter"
                    else if (event.button.x >= quitterRect.x && event.button.x <= quitterRect.x + quitterRect.w &&
                             event.button.y >= quitterRect.y && event.button.y <= quitterRect.y + quitterRect.h) {
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return false;
                    }
                }
                break;
            default:
                break;
        }
    }

    return false;
}