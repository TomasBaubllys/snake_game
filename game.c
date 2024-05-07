// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Definitions of the functions declared in game.h

#include "include/game.h"

GameStatus* initGameStatus(void){
    GameStatus* status = malloc(sizeof(GameStatus));
    if(!status){
        return NULL;
    }

    status->started = false;
    status->gameOver = false;
    status->run = true;
    status->saved = true;
    status->tabPressed = false;
    status->fullscreen = false;
    status->leaderb = false;
    status->leaderbUpdated = false;
    
    return status;
}
