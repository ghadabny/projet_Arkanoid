#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "globals.h"

extern SDL_Rect srcRectsNormalBrick[];
extern SDL_Rect srcRectsHardBrick[];
extern SDL_Rect srcRectsIndestructableBrick[];
extern SDL_Rect srcBackgrounds[];

void draw();
void drawBricks();
void updateAnimations();

#endif // RENDER_H
