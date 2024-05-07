// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Declarations of functions that are used for food logic

#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "game.h"
#include "menu.h"
#include "snake.h"

#define FOOD_SIZE 10
#define FOOD_SIZE_R 40

// snake food structure, used for the object food
typedef struct SnakeFood{
    float x;
    float y;
    int foodSize;
    char *textureName;
}SnakeFood;

// creates food for the start of the game
SnakeFood createFood(void);

// updates the food if the snake ate it
void updateFood(SnakeStruct *mainSnake, SnakeFood *food);

// renders the food to the screen
void renderFood(SDL_Renderer *renderer, bool started, SnakeFood *food, bool radaviciusMode);

#endif // FOOD_H_INCLUDED
