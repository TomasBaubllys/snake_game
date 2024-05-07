// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// The main games cycle and initialize, update and quit functions

#include "include\food.h"
#include "include\menu.h"
#include "include\leaderboard.h"
#include "include\saveload.h"
#include <assert.h>

#ifdef FULLSCREEN
#define SDL_WINDOW_SHOWN SDL_WINDOW_FULLSCREEN
#endif // FULLSCREEN

// initializes everything needed to launch and play the game
bool initialize(SnakeStruct **mainSnake, GameStatus **status, SDL_Window **window, SDL_Renderer **renderer, SnakeFood *food, Leaderboard **leaderboard, int *highScore);

// updates everything happening on the screen
void update(SDL_Renderer *renderer, int highScore, SnakeStruct *mainSnake, int *tempScore, GameStatus *status, SnakeFood *food, TTF_Font *font);

// used at the end of the program to free all of the used memory
void quit(SDL_Window *window, SDL_Renderer *renderer, SnakeStruct *mainSnake, SnakeFood *food, GameStatus *status, Leaderboard *leaderboard);

int main(int argc, char *argv[]){
    atexit(logEnd);
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;
    SnakeStruct *mainSnake = NULL;
    Leaderboard *leaderboard = NULL;
    SnakeFood food;
    int tempScore = 0;
    //Uint32 startTime, endTime;
    GameStatus *status = NULL;
    SDL_Event event;
    int highScore;

    if(!initialize(&mainSnake, &status, &window, &renderer, &food, &leaderboard, &highScore)){
        printf(INIT_ERROR);
        return -1;
    }

    if(!initFont(&font)){
        printf(FONT_INIT_ERROR);
        return -1;
    }

    Uint32 lastTick = SDL_GetTicks();
    //startTime = SDL_GetTicks();

    // main loop
    while(status->run){
        SDL_SetRenderDrawColor(renderer, BACKROUND_C_R, BACKROUND_C_G, BACKROUND_C_B, BACKROUND_C_A);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                status->run = false;
                break;
            }
            if(event.key.keysym.sym == SDLK_q && !status->started && !status->gameOver && !status->tabPressed && !status->leaderb){
                status->run = false;
            }
            if(!status->started && !status->tabPressed && !status->gameOver && !status->leaderb){
                renderMenu(renderer, font);
            }
            if(event.key.keysym.sym == SDLK_SPACE && !status->tabPressed && !status->leaderb){
                status->started = true;
                if(status->gameOver){
                    status->gameOver = false;
                    mainSnake->radaviciusMode = false;
                    status->leaderbUpdated = false;
                }
            }
            if(event.key.keysym.sym == SDLK_ESCAPE){
                status->gameOver = false;
                status->started = false;
                status->tabPressed = false;
                status->leaderb = false;
            }
            if((event.key.keysym.sym == SDLK_TAB || status->tabPressed) && !status->started){
                renderControls(renderer, font);
                status->tabPressed = true;
            }
            if(event.key.keysym.sym == SDLK_f){
                if(!status->fullscreen){
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                    status->fullscreen = true;
                }
                else{
                    SDL_SetWindowFullscreen(window, 0);
                    status->fullscreen = false;
                }
            }
            if(event.key.keysym.sym == SDLK_l && !status->started){
                char *saveFile = renderLoadSave(renderer, font, LOAD_GAME_MSG, LOAD); // add error messages
                if(saveFile){
                    if(!loadGame(mainSnake, saveFile, &food)){
                        resetSnake(mainSnake);
                    }
                    free(saveFile);
                }
            }
            if(event.key.keysym.sym == SDLK_LSHIFT && !status->started && !status->gameOver && !status->saved && !mainSnake->radaviciusMode){
                status->saved = true;
                char *saveFile = renderLoadSave(renderer, font, SAVE_GAME_MSG, SAVE);
                if(saveFile){
                    saveGame(renderer, mainSnake, saveFile, font, food);
                    free(saveFile);
                }
            }
            if(event.key.keysym.sym == SDLK_r){
                if(mainSnake->radaviciusMode){
                    mainSnake->radaviciusMode = false;
                    mainSnake->snakeHead->speed = SNAKE_SPEED;
                    mainSnake->cellSize = SNAKE_SIZE;
                }
                else{
                    mainSnake->radaviciusMode = true;
                    mainSnake->snakeHead->speed = SNAKE_SPEED_R;
                    mainSnake->cellSize = SNAKE_SIZE_R;
                }
            }
            if((event.key.keysym.sym == SDLK_b && !status->started) || status->leaderb){
                status->tabPressed = false;
                status->leaderb = true;
                renderLeaderboard(leaderboard, renderer, font);
            }
        }

        Uint32 currTick = SDL_GetTicks();
        Uint32 diff = currTick - lastTick;

        // limits to ~62 fps
        if(diff < DELAY){
            SDL_Delay((DELAY - diff));
        }

        if(status->gameOver){
            if(!status->leaderbUpdated){
                updateLeaderboard(leaderboard, tempScore, renderer, font);
                status->leaderbUpdated = true;
            }

            if(tempScore > highScore){
                highScore = tempScore;
            }

            renderGameOver(tempScore, renderer, font, mainSnake->radaviciusMode);
            status->saved = true;
        }

        if(status->started && !status->gameOver){
            update(renderer, highScore, mainSnake, &tempScore, status, &food, font);
            //printFPS(&endTime, &startTime);
            status->saved = false;
        }
        lastTick = currTick;
    }

    quit(window, renderer, mainSnake, &food, status, leaderboard);
    return 0;
}

bool initialize(SnakeStruct **mainSnake, GameStatus **status, SDL_Window **window, SDL_Renderer **renderer, SnakeFood *food, Leaderboard **leaderboard, int *highScore){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        return false;
    }

    *window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGTH, SDL_WINDOW_SHOWN);
    if(!window){
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer){
        return false;
    }

    if(TTF_Init() != 0){
        return false;
    }

    *status = initGameStatus();
    if(!status){
        return false;
    }

    *mainSnake = initSnakeStruct();
    if(!mainSnake){
        return false;
    }

    *food = createFood();
    if(!food){
        return false;
    }

    *leaderboard = readLeaderboardFromFile(LEADERBOARD_FILE);
    if(!leaderboard){
        return false;
    }

    *highScore = (*leaderboard)[0].score;

    logStart();

    return true;
}

// quits at the end
void quit(SDL_Window *window, SDL_Renderer *renderer, SnakeStruct *mainSnake, SnakeFood *food, GameStatus *status, Leaderboard *leaderboard){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    destroySnake(mainSnake);
    if(food->textureName){
        free(food->textureName);
    }
    writeLeaderboard(LEADERBOARD_FILE, leaderboard);
    free(leaderboard);

    free(status);
    SDL_Quit();
    TTF_Quit();
}

// updates everything
void update(SDL_Renderer *renderer, int highScore, SnakeStruct *mainSnake, int *tempScore, GameStatus *status, SnakeFood *food, TTF_Font *font){
    SDL_SetRenderDrawColor(renderer, BACKROUND_C_R, BACKROUND_C_G, BACKROUND_C_B, BACKROUND_C_A);
    SDL_RenderClear(renderer);

    updateSnake(mainSnake, &(status->gameOver), tempScore);
    renderSnake(renderer, status->started, mainSnake);

    updateFood(mainSnake, food);
    renderFood(renderer, status->started, food, mainSnake->radaviciusMode);

    renderScore(mainSnake->snakeSize, renderer, font);
    renderHscore(renderer, highScore, font);

    SDL_RenderPresent(renderer);
}


