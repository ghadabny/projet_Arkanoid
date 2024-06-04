#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "globals.h"

int colorLetterToIndex(char colorLetter) ;
void loadLevel();
void resetGameState();
void loadNextLevel();
void resetBallAndPaddle();
void handleBallOutOfBounds();
void reinitGame();

#endif // GAMESTATE_H