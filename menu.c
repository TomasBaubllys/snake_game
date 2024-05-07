// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Definitions of functions found in menu.h file

#include "include\menu.h"

SDL_Color green = {OBJECT_C_R, OBJECT_C_G, OBJECT_C_B, OBJECT_C_A};

bool initFont(TTF_Font **font){
    *font = TTF_OpenFont(FONT, 0);
    if(!(*font)){
        return false;
    }
    return true;
}

bool renderMenu(SDL_Renderer *renderer, TTF_Font *font){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, BACKROUND_C_R, BACKROUND_C_G, BACKROUND_C_B, BACKROUND_C_A);

    renderTextSolid(renderer, font, SNAKE, START_SIZE, WIDTH / 2, HEIGTH / 2, CENTERED);
    renderTextSolid(renderer, font, SPACE_TO_START, PRESS_SPACE_SIZE, WIDTH / 2, HEIGTH / 2 + START_SIZE / 2, CENTERED);
    renderTextSolid(renderer, font, TAB_FOR_CONTROLS, PRESS_TAB_SIZE, PRESS_TAB_MARGIN, HEIGTH - (PRESS_TAB_MARGIN + PRESS_TAB_SIZE / 2), UNCENTERED);

    SDL_RenderPresent(renderer);
    return true;
}

void renderScore(unsigned score, SDL_Renderer *renderer, TTF_Font *font){
    char *scoreStr = malloc(SCORE_LENGTH);
    if(!scoreStr){
        return;
    }

    sprintf(scoreStr, SCORE_FORMAT, (score - 2));

    renderTextSolid(renderer, font, scoreStr, SCORE_SIZE, SCORE_MARGIN, SCORE_MARGIN, UNCENTERED);
    renderUpperLine(renderer);

    free(scoreStr);

    return;
}

void renderGameOver(unsigned score, SDL_Renderer *renderer, TTF_Font *font, bool radaviciusMode){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, BACKROUND_C_R, BACKROUND_C_G, BACKROUND_C_B, BACKROUND_C_A);

    renderTextSolid(renderer, font, GAME_OVER_MSG, GAME_OVER_SIZE, WIDTH / 2, HEIGTH / 2, CENTERED);

    char *scoreStr = malloc(SCORE_LENGTH);
    if(!scoreStr){
        return;
    }
    sprintf(scoreStr, SCORE_FORMAT, score);

    renderTextSolid(renderer, font, scoreStr, PRESS_SPACE_SIZE, WIDTH / 2, HEIGTH / 2 + GAME_OVER_SIZE / 2, CENTERED);

    if(radaviciusMode){
        SDL_Texture *gameOverRTexture = NULL;
        SDL_Surface *gameOverRSurface = NULL;
        SDL_RenderClear(renderer);
        gameOverRSurface = SDL_LoadBMP(GAME_OVER_TEX);
        gameOverRTexture = SDL_CreateTextureFromSurface(renderer, gameOverRSurface);

        SDL_RenderCopy(renderer, gameOverRTexture, NULL, &(SDL_Rect){
                                                        .x = (WIDTH / 2) - (gameOverRSurface->w / 2),
                                                        .y = (HEIGTH / 2) - (gameOverRSurface->h / 2),
                                                        .w = gameOverRSurface->w,
                                                        .h = gameOverRSurface->h
                                                        });
        SDL_DestroyTexture(gameOverRTexture);
        SDL_FreeSurface(gameOverRSurface);
    }

    SDL_RenderPresent(renderer);
}

void renderHscore(SDL_Renderer *renderer, int hScore, TTF_Font *font){ // hard to automate:((
    char *hScoreStr = malloc(HSCORE_SIZE);
    if(!hScoreStr){
        return;
    }
    sprintf(hScoreStr, HIGHSCORE_FORMAT, hScore);

    TTF_SetFontSize(font, SCORE_SIZE);
    SDL_Surface *hScoreSurface = TTF_RenderText_Solid(font, hScoreStr, green);
    SDL_Texture *hScoreTexture = SDL_CreateTextureFromSurface(renderer, hScoreSurface);

    SDL_RenderCopy(renderer, hScoreTexture, NULL, &(SDL_Rect){
                                                    .x = WIDTH - (hScoreSurface->w + SCORE_MARGIN),
                                                    .y = SCORE_MARGIN,
                                                    .w = hScoreSurface->w,
                                                    .h = hScoreSurface->h
                                                    });
    SDL_DestroyTexture(hScoreTexture);
    SDL_FreeSurface(hScoreSurface);
    free(hScoreStr);
}

bool renderControls(SDL_Renderer *renderer, TTF_Font *font){
    SDL_RenderClear(renderer);

    const char *controlsMessages[] = {CONTROLS_MSG_1, CONTROLS_MSG_2, CONTROLS_MSG_3,
                                      CONTROLS_MSG_4, CONTROLS_MSG_5, CONTROLS_MSG_6,
                                      CONTROLS_MSG_7, CONTROLS_MSG_8, CONTROLS_MSG_9,
                                      CONTROLS_MSG_10};


    for(int i = 0; i < CONTROLS_MSG_COUNT; ++i){
        renderTextSolid(renderer, font, controlsMessages[i], CONTROLS_SIZE, CONTROLS_MARGIN, CONTROLS_MARGIN * (i + 1)  + CONTROLS_SIZE * i, UNCENTERED);
    }

    SDL_RenderPresent(renderer);
    return true;
}

char *renderLoadSave(SDL_Renderer *renderer, TTF_Font *font, const char *header, bool loadSave){
    SDL_Event event;
    short index = 0;
    short counter = 0;
    bool noGamesToLoad = false;

    char **fileNames = readFiles(DATA_FOLDER, &counter);
    if(!fileNames && loadSave == LOAD){
        noGamesToLoad = true;

        fileNames = calloc(sizeof(char*), 1);
        if(!fileNames){
            return NULL;
        }

        counter = 1;

        fileNames[counter - 1] = calloc(sizeof(char), strlen(NO_SAVE_GAMES_MSG) + 1);
        if(!fileNames[counter - 1]){
            return NULL;
        }
        strcpy(fileNames[counter - 1], NO_SAVE_GAMES_MSG);
    }

    if(counter < MAX_SAVEGAMES && loadSave == SAVE){
        fileNames = realloc(fileNames, sizeof(char*) * (counter + 1));
        if(!fileNames){
            return NULL;
        }

        fileNames[counter] = malloc(sizeof(DATA));
        if(!fileNames[counter]){
            return NULL;
        }
        strcpy(fileNames[counter], NEW);
        ++counter;
    }

    SDL_Rect choosingpoint = {
    .x = LINE_MARGIN,
    .y = LINE_MARGIN + SCORE_SIZE + SCORE_MARGIN * 2 + CHOOSING_POINT_MARGIN,
    .w = CHOOSING_POINT_SIZE,
    .h = CHOOSING_POINT_SIZE
    };


    while(1){
        SDL_RenderClear(renderer);
        renderTextSolid(renderer, font, header, SAVE_GAMESIZE, SCORE_MARGIN, SCORE_MARGIN, UNCENTERED);

        renderUpperLine(renderer);
        SDL_SetRenderDrawColor(renderer, OBJECT_C_R, OBJECT_C_G, OBJECT_C_B, OBJECT_C_A);
        SDL_RenderFillRect(renderer, &choosingpoint);
        SDL_SetRenderDrawColor(renderer, BACKROUND_C_R, BACKROUND_C_G, BACKROUND_C_B, BACKROUND_C_A);

        for(short i = 0; i < counter; ++i){
            renderTextSolid(renderer, font, fileNames[i], SAVE_GAMESIZE, LINE_MARGIN * 2 + CHOOSING_POINT_SIZE, LINE_MARGIN * (i + 1) + SAVE_GAMESIZE * i + SCORE_SIZE + SCORE_MARGIN * 2 + LINE_WIDTH, UNCENTERED);
        }

        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_s:
                        if(index < counter - 1){
                            choosingpoint.y += SAVE_GAMESIZE + LINE_MARGIN;
                            ++index;
                        }
                        else{
                            choosingpoint.y -= (SAVE_GAMESIZE + LINE_MARGIN) * (counter - 1);
                            index = 0;
                        }
                        break;

                    case SDLK_w:
                        if(index > 0){
                            choosingpoint.y -= SAVE_GAMESIZE + LINE_MARGIN;
                            --index;
                        }
                        else{
                            choosingpoint.y += (SAVE_GAMESIZE + LINE_MARGIN) * (counter - 1);
                            index = counter - 1;
                        }
                        break;

                    case SDLK_RETURN:
                        if(!noGamesToLoad){
                            char *saveFile = malloc(strlen(fileNames[index]) + 1);
                            strcpy(saveFile, fileNames[index]);
                            for(short i = 0; i < counter; ++i){
                                free(fileNames[i]);
                            }
                            free(fileNames);
                            return saveFile;
                        }
                        break;

                    case SDLK_ESCAPE:
                        for(short i = 0; i < counter; ++i){
                            free(fileNames[i]);
                            fileNames[i] = NULL;
                        }
                        free(fileNames);
                        fileNames = NULL;
                        return NULL;

                    case SDLK_DELETE:
                        char *pathToFile = calloc(sizeof(char), strlen(fileNames[index]) + DATA);
                        if(!pathToFile){
                            break;
                        }

                        sprintf(pathToFile, DATA_DIR, fileNames[index]);
                        if(remove(pathToFile) == 0){
                            for(short i = 0; i < counter; ++i){
                                free(fileNames[i]);
                                fileNames[i] = NULL;
                            }
                            free(fileNames);
                            fileNames = NULL;

                            fileNames = readFiles(DATA_FOLDER, &counter);
                            if(loadSave == SAVE){
                                fileNames = realloc(fileNames, sizeof(char*) * (counter + 1));
                                if(!fileNames){
                                    return NULL;
                                }

                                fileNames[counter] = malloc(sizeof(DATA));
                                if(!fileNames[counter]){
                                    return NULL;
                                }
                                strcpy(fileNames[counter], NEW);

                                ++counter;
                            }
                        }
                        free(pathToFile);
                        break;
                }
            }
        }
    }
    return NULL;
}

char *renderInputString(SDL_Renderer *renderer, TTF_Font *font, const char *header){
    char *fileName = malloc(MAX_FILE_LENGTH - DATA * sizeof(char));
    if(!fileName){
        return NULL;
    }
    short letterCounter = 0;

    SDL_Event event;
    while(1){
        SDL_SetRenderDrawColor(renderer, OBJECT_C_R, OBJECT_C_G, OBJECT_C_B, OBJECT_C_A);
        renderUpperLine(renderer);
        SDL_SetRenderDrawColor(renderer, BACKROUND_C_R, BACKROUND_C_G, BACKROUND_C_B, BACKROUND_C_A);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                if((event.key.keysym.sym >= 97 && event.key.keysym.sym <= 122) || (event.key.keysym.sym >= 48 && event.key.keysym.sym <= 57)){
                    if(letterCounter < MAX_FILE_NAME){
                        fileName[letterCounter] = (char)event.key.keysym.sym;
                        ++letterCounter;
                        fileName[letterCounter] = '\0';
                    }
                }
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    free(fileName);
                    return NULL;
                }
                if(event.key.keysym.sym == SDLK_BACKSPACE){
                    if(letterCounter > 0){
                        --letterCounter;
                        fileName[letterCounter] = '\0';
                    }
                }
                if(event.key.keysym.sym == SDLK_RETURN){
                    return fileName;
                }
            }
        }

        renderTextSolid(renderer, font, header, SAVE_GAMESIZE, SCORE_MARGIN, SCORE_MARGIN, UNCENTERED);

        if(letterCounter > 0){
            renderTextSolid(renderer, font, fileName, SAVE_GAMESIZE, SCORE_MARGIN, SCORE_MARGIN * 2 + SCORE_SIZE + LINE_WIDTH + LINE_MARGIN, UNCENTERED);
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
    return NULL;
}

bool renderTextSolid(SDL_Renderer *renderer, TTF_Font *font, const char *str, unsigned fontSize, unsigned xPos, unsigned yPos, bool centered){
    if(!font || !str){
        return false;
    }

    if(TTF_SetFontSize(font, fontSize) == -1){
        return false;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, str, green);
    if(!surface){
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!texture){
        return false;
    }

    SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){
                        .x = centered? xPos - surface->w / 2 : xPos,
                        .y = centered? yPos - surface->h / 2 : yPos,
                        .w = surface->w,
                        .h = surface->h
                       });

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    return true;
}

void renderUpperLine(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, OBJECT_C_R, OBJECT_C_G, OBJECT_C_B, OBJECT_C_A);

    SDL_Rect upperLine = {
    .x = LINE_WIDTH + LINE_MARGIN,
    .y = (SCORE_MARGIN * 2) + SCORE_SIZE,
    .w = WIDTH - ((LINE_WIDTH + LINE_MARGIN) * 2),
    .h = LINE_WIDTH
    };

    SDL_RenderFillRect(renderer, &upperLine);
    SDL_SetRenderDrawColor(renderer, BACKROUND_C_R, BACKROUND_C_G, BACKROUND_C_B, BACKROUND_C_A);
}
