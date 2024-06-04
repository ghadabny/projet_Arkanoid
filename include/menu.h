#ifndef MENU_H
#define MENU_H

#include <stdbool.h> // Inclusion de stdbool.h pour le type de données bool
#include <SDL2/SDL.h>

// Fonction pour afficher le menu principal et gérer les clics sur les boutons
bool afficher_menu(SDL_Window* window, SDL_Surface* surface);


#endif // MENU_H