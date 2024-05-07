// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Declarations of functions that are used for snakes logic

#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "menu.h"

#define START_CELL_COUNT 2
#define SNAKE_SIZE 20
#define SNAKE_SPEED 20
#define SNAKE_RATE 4
#define SNAKE_SPEED_R 50
#define SNAKE_SIZE_R 50

typedef struct SnakeCell{
    float x;
    float y;
    int speed;
    struct SnakeCell *next;
    struct SnakeCell *prev;
}SnakeCell;

typedef struct SnakeMovement{
    bool up;
    bool down;
    bool left;
    bool right;
}SnakeMovement;

typedef struct SnakeStruct{
    SnakeCell *snakeHead;
    SnakeCell *snakeTail;
    unsigned cellSize;
    SnakeMovement movement;
    unsigned snakeDrawn;
    unsigned snakeSize;
    unsigned shouldMove;
    bool radaviciusMode;
}SnakeStruct;

// creates the snakes heads
SnakeCell *createSnake(void);

// creates a new cell to the snakes tail
SnakeCell *addCellSnake(SnakeCell *snakeTail);

// creates a snake tail, links it to the head
SnakeCell *createSnakeTail(SnakeCell *snakeHead);

// initializes the main snakes struct
SnakeStruct *initSnakeStruct(void);

// resets the snake to two cells, reset other stats
void resetSnake(SnakeStruct *mainSnake);

// renders the snake to the screen
void renderSnake(SDL_Renderer *renderer, bool started, SnakeStruct *mainSnake);

// updates snakes cells positions
void updateSnake(SnakeStruct *mainSnake, bool *gameOver, unsigned *tempScore);

// checks if the snake collided with itself
bool snakeCollision(SnakeCell *snakeHead);

// destroys the snake, clears memory
void destroySnake(SnakeStruct *mainSnake);

// checks if the snake has went out of borders
void snakeBorderControl(SnakeStruct *mainSnake);

// moves the snakes head on the screen
void moveSnake(SnakeStruct *mainSnake);

// updates the snakes cells positions (all except the head)
void updateCellPosition(SnakeStruct *mainSnake);

// registers users input for snake
void registerInputSnake(SnakeStruct *mainSnake);

#endif // SNAKE_H_INCLUDED
