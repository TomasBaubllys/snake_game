// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Definitions of functions declared in saveload.h

#include "include/saveload.h"

bool saveGame(SDL_Renderer *renderer , SnakeStruct *mainSnake, const char *fileName, TTF_Font *font, SnakeFood food){
    char *fullSaveFile = malloc(MAX_FILE_LENGTH);
    if(!fullSaveFile){
        return false;
    }

    if(strcmp(fileName, NEW) == 0){
        char *saveFile = renderInputString(renderer, font, NEW_SAVEGAME_HEADER);
        if(!saveFile){
            return false;
        }

        addDotBin(saveFile);

        if(!endsInBin(saveFile)){
            free(saveFile);
            return false;
        }
        sprintf(fullSaveFile, DATA_DIR, saveFile);
        free(saveFile);
    }
    else{
        sprintf(fullSaveFile, DATA_DIR, fileName);
    }

    FILE *sGamePtr = fopen(fullSaveFile, "wb");
    if(!sGamePtr){
        free(fullSaveFile);
        return false;
    }

    fwrite(&(food.x), sizeof(float), 1, sGamePtr);
    fwrite(&(food.y), sizeof(float), 1, sGamePtr);

    fwrite(&(mainSnake->snakeDrawn), sizeof(unsigned), 1, sGamePtr);
    fwrite(&(mainSnake->snakeSize), sizeof(unsigned), 1, sGamePtr);
    fwrite(&(mainSnake->movement), sizeof(SnakeMovement), 1, sGamePtr);

    SnakeCell *temp = mainSnake->snakeHead;
    while(temp){
        fwrite(temp, sizeof(SnakeCell), 1, sGamePtr);
        temp = temp->next;
    }

    free(fullSaveFile);
    fclose(sGamePtr);
    return true;
}

bool loadGame(SnakeStruct *mainSnake, const char *fileName, SnakeFood *food){
    if(!fileName){
        return false;
    }

    char *fullSaveFile = malloc(MAX_FILE_LENGTH);
    if(!fullSaveFile){
        return false;
    }

    sprintf(fullSaveFile, DATA_DIR, fileName);
    FILE *lGamePtr = fopen(fullSaveFile, "rb");
    if(!lGamePtr){
        free(fullSaveFile);
        return false;
    }

    fread(&food->x, sizeof(float), 1, lGamePtr);
    fread(&food->y, sizeof(float), 1, lGamePtr);

    fread(&(mainSnake->snakeDrawn), sizeof(unsigned), 1, lGamePtr);
    fread(&(mainSnake->snakeSize), sizeof(unsigned), 1, lGamePtr);
    fread(&(mainSnake->movement), sizeof(SnakeMovement), 1, lGamePtr);
    fread(mainSnake->snakeHead, sizeof(SnakeCell), 1, lGamePtr);

    SnakeCell *temp = mainSnake->snakeHead;
    SnakeCell *rTemp = NULL;
    while(temp->next){
        rTemp = (SnakeCell*)malloc(sizeof(SnakeCell));
        if(!rTemp){
            return false;
        }
        
        fread(rTemp, sizeof(SnakeCell), 1, lGamePtr);
        temp->next = rTemp;
        rTemp->prev = temp;
        temp = temp->next;
    }

    fread(mainSnake->snakeTail, sizeof(SnakeCell), 1, lGamePtr);
    mainSnake->snakeTail->prev = rTemp;
    rTemp->next = mainSnake->snakeTail;

    mainSnake->radaviciusMode = false;
    mainSnake->cellSize = SNAKE_SIZE;
    mainSnake->snakeHead->speed = SNAKE_SPEED;

    fclose(lGamePtr);
    free(fullSaveFile);

    return true;
}
