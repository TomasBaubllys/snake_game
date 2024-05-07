#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH_TEST 640
#define HEIGTH_TEST 480

#define SNAKE_SIZE_TEST 20
#define START_CELL_COUNT_TEST 2
#define SNAKE_SPEED_TEST 20

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

// creates a new cell to the snakes tail <--- function to be tested
SnakeCell *addCellSnake(SnakeCell *snakeTail);

// creates a snake tail, links it to the head
SnakeCell *createSnakeTail(SnakeCell *snakeHead);

// initializes the main snakes struct
SnakeStruct *initSnakeStruct(void);

int main(void){
    SnakeStruct *testSnake = initSnakeStruct();
    addCellSnake(testSnake->snakeTail);
    assert(testSnake->snakeTail->x == testSnake->snakeTail->prev->x);
    assert(testSnake->snakeTail->x == testSnake->snakeTail->prev->x);

    int counter = 0;
    SnakeCell *temp = testSnake->snakeHead;

    while(temp){
        temp = temp->next;
        ++counter;
    }

    assert(counter == 3);
    return 0;
}

SnakeStruct* initSnakeStruct(void){
    SnakeStruct *mainSnake = malloc(sizeof(SnakeStruct));
    if(!mainSnake){
        return NULL;
    }
    mainSnake->snakeHead = createSnake();
    mainSnake->snakeTail = createSnakeTail(mainSnake->snakeHead);
    mainSnake->cellSize = SNAKE_SIZE_TEST;
    mainSnake->snakeSize = START_CELL_COUNT_TEST;
    mainSnake->snakeDrawn = START_CELL_COUNT_TEST;
    mainSnake->movement.up = true;
    mainSnake->movement.down = false;
    mainSnake->movement.left = false;
    mainSnake->movement.right = false;
    mainSnake->radaviciusMode = false;
    mainSnake->shouldMove = 0;
    return mainSnake;
}


SnakeCell *createSnake(){
    SnakeCell *newSnake = malloc(sizeof(SnakeCell));
    if(!newSnake){
        NULL;
    }
    newSnake->speed = SNAKE_SPEED_TEST;
    newSnake->x = WIDTH_TEST / 2;
    newSnake->y = HEIGTH_TEST / 2;
    newSnake->next = NULL;
    newSnake->prev = NULL;

    return newSnake;
}

// function to test
SnakeCell *addCellSnake(SnakeCell *snakeTail){
    SnakeCell *newCell = createSnake();
    if(newCell == NULL){
        return NULL;
    }
    snakeTail->next = newCell;
    newCell->prev = snakeTail;
    newCell->x = snakeTail->x; // coordinates updated later accordingly
    newCell->y = snakeTail->y;
    return newCell;
}
// function to test

SnakeCell *createSnakeTail(SnakeCell *snakeHead){
    SnakeCell *newTail = createSnake();
    if(newTail == NULL){
        return NULL;
    }
    newTail->y = snakeHead->y + SNAKE_SIZE_TEST;
    newTail->prev = snakeHead;
    snakeHead->next = newTail;
    return newTail;
}

