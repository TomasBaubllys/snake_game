// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Definitions of functions declared in the leaderboard.h file

#include "include\leaderboard.h"
#include "include\menu.h"

Leaderboard* readLeaderboardFromFile(const char *fileName){
    Leaderboard *leaderboard = calloc(sizeof(Leaderboard), MAX_SCORES_TRACKED);

    FILE *fptr = fopen(fileName, "rb");
    if(!fptr){
        for(int i = 0; i < MAX_SCORES_TRACKED; ++i){
            leaderboard[i].nameLength = strlen(NO_REG_SCORE_NAME);
            leaderboard[i].name = calloc(sizeof(char), strlen(NO_REG_SCORE_NAME) + 1);
            strcpy(leaderboard[i].name, NO_REG_SCORE_NAME);
            leaderboard[i].score = NO_REG_SCORE_SCORE;
        }
    }
    else{
        for(int i = 0; i < MAX_SCORES_TRACKED; ++i){
            fread(&(leaderboard[i].nameLength), sizeof(int), 1, fptr);
            leaderboard[i].name = calloc(sizeof(char), leaderboard[i].nameLength + 1);
            fread(leaderboard[i].name, sizeof(char), leaderboard[i].nameLength + 1, fptr);
            fread(&(leaderboard[i].score), sizeof(int), 1, fptr);
        }
        fclose(fptr);
    }
    return leaderboard;
}

void writeLeaderboard(const char *fileName, Leaderboard *leaderboard){
    FILE *fptr = fopen(fileName, "wb");
    for(int i = 0; i < MAX_SCORES_TRACKED; ++i){
        fwrite(&leaderboard[i].nameLength, sizeof(int), 1, fptr);
        fwrite(leaderboard[i].name, sizeof(char), leaderboard[i].nameLength + 1, fptr);
        fwrite(&leaderboard[i].score, sizeof(int), 1, fptr);
    }
    fclose(fptr);
}

void renderLeaderboard(Leaderboard *leaderboard, SDL_Renderer *renderer, TTF_Font *font){
    SDL_RenderClear(renderer);
    char *tempScore = NULL;

    renderTextSolid(renderer, font, LEADERBOARD_HEADER, SAVE_GAMESIZE, SCORE_MARGIN, SCORE_MARGIN, UNCENTERED);
    renderUpperLine(renderer);

    for(short i = 0; i < MAX_SCORES_TRACKED; ++i){
        tempScore = calloc(sizeof(char), MAX_SCORE_LENGTH + leaderboard[i].nameLength + 1 + LEADERBOARD_EXTRA_MEMORY);
        if(!tempScore){
            return;
        }

        sprintf(tempScore, LEADERBOARD_FORMAT, leaderboard[i].name, leaderboard[i].score);

        renderTextSolid(renderer, font, tempScore, SAVE_GAMESIZE,  SCORE_MARGIN, LINE_MARGIN * (i + 1) + SAVE_GAMESIZE * i + SCORE_SIZE + SCORE_MARGIN * 2 + LINE_WIDTH, UNCENTERED);
        free(tempScore);
    }
    SDL_RenderPresent(renderer);
}

void updateLeaderboard(Leaderboard *leaderboard, int newScore, SDL_Renderer *renderer, TTF_Font *font){
    if(newScore > leaderboard[LAST_SCORE_ID].score){
        renderNewHScore(renderer, font);
        leaderboard[LAST_SCORE_ID].score = newScore;

        free(leaderboard[LAST_SCORE_ID].name);
        leaderboard[LAST_SCORE_ID].name = renderInputString(renderer, font, ENTER_NAME);

        if(!leaderboard[LAST_SCORE_ID].name){
            leaderboard[LAST_SCORE_ID].name = noNameEntered();
        }

        leaderboard[LAST_SCORE_ID].nameLength = strlen(leaderboard[LAST_SCORE_ID].name);
        sortLeaderboard(leaderboard);
        return;
    }
}

void sortLeaderboard(Leaderboard *leaderboard){
    for(int i = 0; i < MAX_SCORES_TRACKED; ++i){
        for(int j = 0; j < MAX_SCORES_TRACKED - i - 1; ++j){
            if(leaderboard[j].score < leaderboard[j + 1].score){
                Leaderboard tempLead = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = tempLead;
            }
        }
    }
}

void renderNewHScore(SDL_Renderer *renderer, TTF_Font *font){
    SDL_Event event;
    while(1){
        SDL_RenderClear(renderer);
        while(SDL_PollEvent(&event)){
            if(event.key.keysym.sym == SDLK_SPACE){
                return;
            }
        }
        renderTextSolid(renderer, font, NEW_SCORE_HEADER, HIGHSCORE_SIZE, WIDTH / 2, HEIGTH / 2, CENTERED);
        renderTextSolid(renderer, font, PRESS_SPACE_C_MSG, PRESS_SPACE_SIZE, WIDTH / 2, HEIGTH / 2 + GAME_OVER_SIZE / 2, CENTERED);
        SDL_RenderPresent(renderer);
    }
}

void freeLeaderboard(Leaderboard *leaderboard){
    if(!leaderboard){
        return;
    }
    
    for(short i = 0; i < MAX_SCORES_TRACKED; ++i){
        if(leaderboard[i].name){
            free(leaderboard[i].name);
        }
    }
    free(leaderboard);
}
