// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Declarations of functions that are used for saving and loading the game

#ifndef SAVELOAD_H_INCLUDED
#define SAVELOAD_H_INCLUDED

#include "game.h"
#include "snake.h"
#include "food.h"

// saves the current game to a file
bool saveGame(SDL_Renderer *renderer, SnakeStruct *mainSnake, const char *fileName, TTF_Font *font, SnakeFood food);

// loads the game from a file
bool loadGame(SnakeStruct *mainSnake, const char *fileName, SnakeFood *food);

#endif // SAVELOAD_H_INCLUDED
