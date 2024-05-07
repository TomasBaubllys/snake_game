// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Definitions of functions declared in the food.h file

#include "include\food.h"

SnakeFood createFood(void){
    SnakeFood food;
    food.x = randPixel(WIDTH - FOOD_SIZE, 0);
    food.y = randPixel(HEIGTH, (SCORE_SIZE + SCORE_MARGIN * 2 + LINE_WIDTH));
    food.foodSize = FOOD_SIZE;
    food.textureName = NULL;
    return food;
}

void updateFood(SnakeStruct *mainSnake, SnakeFood *food){
    SDL_Rect snakeCurrRect = {
        .x = mainSnake->snakeHead->x,
        .y = mainSnake->snakeHead->y,
        .w = mainSnake->cellSize,
        .h = mainSnake->cellSize
    };
    SDL_Rect foodRect = {
        .x = food->x,
        .y = food->y,
        .w = food->foodSize,
        .h = food->foodSize
    };

    if(mainSnake->radaviciusMode){
        foodRect.w = FOOD_SIZE_R;
        foodRect.h = FOOD_SIZE_R;
    }

    if(SDL_HasIntersection(&snakeCurrRect, &foodRect)){
        ++(mainSnake->snakeSize);
        food->x = randPixel(WIDTH - FOOD_SIZE, 0);
        food->y = randPixel(HEIGTH - FOOD_SIZE, (SCORE_SIZE + SCORE_MARGIN * 2 + LINE_WIDTH));

        if(mainSnake->radaviciusMode){
            short counter = 0;
            short index = 0;
            char **textureFile = readFiles(STUDENTS_FOLDER, &counter);

            if(!textureFile){
                food->textureName = NULL;
                return;
            }

            index  = randPixel(counter - 1, 0);
            char *fullName = malloc(sizeof(char*) * MAX_FILE_LENGTH);
            if(!fullName){
                for(short i = 0; i < counter; ++i){
                    free(textureFile[i]);
                }
                free(textureFile);
                food->textureName = false;
                return;
            }

            sprintf(fullName, STUDENTS_DIR, textureFile[index]);
            food->textureName = fullName;
            for(short i = 0; i < counter; ++i){
                free(textureFile[i]);
            }
            
            free(textureFile);
        }
    }
}

void renderFood(SDL_Renderer *renderer, bool started, SnakeFood *food, bool radaviciusMode){
    if(started){
        SDL_SetRenderDrawColor(renderer, OBJECT_C_R, OBJECT_C_G, OBJECT_C_B, OBJECT_C_A);
        SDL_Rect foodRect ={
            .x = food->x,
            .y = food->y,
            .w = food->foodSize,
            .h = food->foodSize
        };
        if(radaviciusMode && food->textureName){
            foodRect.w = FOOD_SIZE_R;
            foodRect.h = FOOD_SIZE_R;
            SDL_Surface *foodSurface = SDL_LoadBMP(food->textureName);
            SDL_Texture *foodTexture = SDL_CreateTextureFromSurface(renderer, foodSurface);
            SDL_RenderCopy(renderer, foodTexture, NULL, &foodRect);
            SDL_DestroyTexture(foodTexture);
            SDL_FreeSurface(foodSurface);
        }
        else{
            SDL_RenderFillRect(renderer, &foodRect);
        }
    }
}
