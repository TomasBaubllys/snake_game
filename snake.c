// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Definitions of functions declared in the snake.h file

#include "include\snake.h"

SnakeStruct* initSnakeStruct(void){
    SnakeStruct *mainSnake = malloc(sizeof(SnakeStruct));
    if(!mainSnake){
        return NULL;
    }
    mainSnake->snakeHead = createSnake();
    mainSnake->snakeTail = createSnakeTail(mainSnake->snakeHead);
    mainSnake->cellSize = SNAKE_SIZE;
    mainSnake->snakeSize = START_CELL_COUNT;
    mainSnake->snakeDrawn = START_CELL_COUNT;
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
       return NULL;
    }

    newSnake->speed = SNAKE_SPEED;
    newSnake->x = WIDTH / 2;
    newSnake->y = HEIGTH / 2;
    newSnake->next = NULL;
    newSnake->prev = NULL;

    return newSnake;
}

SnakeCell *addCellSnake(SnakeCell *snakeTail){
    SnakeCell *newCell = createSnake();
    if(!newCell){
        return NULL;
    }

    snakeTail->next = newCell;
    newCell->prev = snakeTail;
    newCell->x = snakeTail->x; // coordinates updated later accordingly
    newCell->y = snakeTail->y;

    return newCell;
}

SnakeCell *createSnakeTail(SnakeCell *snakeHead){
    SnakeCell *newTail = createSnake();
    if(newTail == NULL){
        return NULL;
    }
    newTail->y = snakeHead->y + SNAKE_SIZE;
    newTail->prev = snakeHead;
    snakeHead->next = newTail;
    return newTail;
}

void resetSnake(SnakeStruct *mainSnake){
    SnakeCell *temp = mainSnake->snakeHead;
    SnakeCell *next;
    mainSnake->cellSize = SNAKE_SIZE;
    while(temp){
        next = temp->next;
        free(temp);
        temp = next;
    }
    mainSnake->snakeHead = createSnake();
    mainSnake->snakeTail = createSnakeTail(mainSnake->snakeHead);
    mainSnake->movement.up = true;
    mainSnake->movement.down = false;
    mainSnake->movement.left = false;
    mainSnake->movement.right = false;
    mainSnake->snakeDrawn = START_CELL_COUNT;
    mainSnake->snakeSize = START_CELL_COUNT;
}

void renderSnake(SDL_Renderer *renderer, bool started, SnakeStruct *mainSnake){
    if(started){
        SDL_SetRenderDrawColor(renderer, OBJECT_C_R, OBJECT_C_G, OBJECT_C_B, OBJECT_C_A);
        SnakeCell *temp = mainSnake->snakeHead;
        while(temp){
            SDL_Rect snakeRect ={
                .x = temp->x,
                .y = temp->y,
                .w = mainSnake->cellSize,
                .h = mainSnake->cellSize
            };
            SDL_RenderFillRect(renderer, &snakeRect);
            temp = temp->next;
        }

        if(mainSnake->radaviciusMode){ // probably cost a lot of memory to constantly load the same file??
            SDL_Surface *rSurface = SDL_LoadBMP(RADAVICIUS_TEX);
            SDL_Texture *rTexture = SDL_CreateTextureFromSurface(renderer, rSurface);
            SDL_RenderCopy(renderer, rTexture, NULL, &(SDL_Rect){
                                                .x = mainSnake->snakeHead->x,
                                                .y = mainSnake->snakeHead->y,
                                                .w = mainSnake->cellSize,
                                                .h = mainSnake->cellSize
                                                });
            SDL_DestroyTexture(rTexture);
            SDL_FreeSurface(rSurface);
        }
    }
}

void updateSnake(SnakeStruct *mainSnake, bool *gameOver, unsigned *tempScore){
    if(mainSnake->snakeDrawn < mainSnake->snakeSize){
        mainSnake->snakeTail = addCellSnake(mainSnake->snakeTail);
        ++(mainSnake->snakeDrawn);
    }

    updateCellPosition(mainSnake);
    registerInputSnake(mainSnake);
    moveSnake(mainSnake);
    snakeBorderControl(mainSnake);

    if(snakeCollision(mainSnake->snakeHead)){
        *gameOver = true;
        *tempScore = mainSnake->snakeSize - 2;
        resetSnake(mainSnake);
    }
    ++(mainSnake->shouldMove);
}

bool snakeCollision(SnakeCell *snakeHead){
    SDL_Rect headRect = {
    .x = snakeHead->x,
    .y = snakeHead->y,
    .w = SNAKE_SIZE,
    .h = SNAKE_SIZE,
    };

    SnakeCell *temp = snakeHead->next;
    while(temp){
        SDL_Rect bodyRect = {
        .x = temp->x,
        .y = temp->y,
        .w = SNAKE_SIZE,
        .h = SNAKE_SIZE
        };
        if(SDL_HasIntersection(&headRect, &bodyRect)){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void destroySnake(SnakeStruct *mainSnake){
    resetSnake(mainSnake);
    free(mainSnake->snakeHead);
    free(mainSnake->snakeTail);
    free(mainSnake);
}

void snakeBorderControl(SnakeStruct *mainSnake){
    if(mainSnake->snakeHead->x >= WIDTH ){
        mainSnake->snakeHead->x = 0;
    }

    if(mainSnake->snakeHead->x < 0){
        mainSnake->snakeHead->x = WIDTH - mainSnake->cellSize;
    }

    if(mainSnake->snakeHead->y >= HEIGTH){
        mainSnake->snakeHead->y = LINE_WIDTH + SCORE_MARGIN * 2 + SCORE_SIZE;
    }

    if(mainSnake->snakeHead->y < LINE_WIDTH + SCORE_MARGIN + SCORE_SIZE){
        mainSnake->snakeHead->y = HEIGTH - mainSnake->cellSize;
    }
}

void moveSnake(SnakeStruct *mainSnake){
    if(mainSnake->movement.right && mainSnake->shouldMove >= SNAKE_RATE){
        mainSnake->snakeHead->x += mainSnake->snakeHead->speed;
        mainSnake->shouldMove = 0;
    }

    if(mainSnake->movement.left && mainSnake->shouldMove >= SNAKE_RATE){
        mainSnake->snakeHead->x -= mainSnake->snakeHead->speed;
        mainSnake->shouldMove = 0;
    }

    if(mainSnake->movement.up && mainSnake->shouldMove >= SNAKE_RATE){
        mainSnake->snakeHead->y -= mainSnake->snakeHead->speed;
        mainSnake->shouldMove = 0;
    }

    if(mainSnake->movement.down && mainSnake->shouldMove >= SNAKE_RATE){
        mainSnake->snakeHead->y += mainSnake->snakeHead->speed;
        mainSnake->shouldMove = 0;
    }
}

void updateCellPosition(SnakeStruct *mainSnake){
    if(mainSnake->shouldMove >= SNAKE_RATE && mainSnake->snakeSize > 1){
        SnakeCell *temp = mainSnake->snakeTail;

        while(temp != mainSnake->snakeHead){
            temp->x = temp->prev->x;
            temp->y = temp->prev->y;
            temp = temp->prev;
        };
    }
}

void registerInputSnake(SnakeStruct *mainSnake){
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    if(keyboardState[SDL_SCANCODE_D] && !(mainSnake->movement.left)){
        mainSnake->movement.right = true;
        mainSnake->movement.left = false;
        mainSnake->movement.up = false;
        mainSnake->movement.down = false;
    };

    if(keyboardState[SDL_SCANCODE_A] && !(mainSnake->movement.right)){
        mainSnake->movement.right = false;
        mainSnake->movement.left = true;
        mainSnake->movement.up = false;
        mainSnake->movement.down = false;
    };

    if(keyboardState[SDL_SCANCODE_W] && !(mainSnake->movement.down)){
        mainSnake->movement.right = false;
        mainSnake->movement.left = false;
        mainSnake->movement.up = true;
        mainSnake->movement.down = false;
    };

    if(keyboardState[SDL_SCANCODE_S] && !(mainSnake->movement.up)){
        mainSnake->movement.right = false;
        mainSnake->movement.left = false;
        mainSnake->movement.up = false;
        mainSnake->movement.down = true;
    };
}
