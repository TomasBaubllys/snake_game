// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Declarations of functions that are used for the leaderboards logic in the game

#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

#include "game.h"

#define NO_REG_SCORE_NAME "_ _ _ _ _ _"
#define NO_REG_SCORE_SCORE 0
#define MAX_SCORES_TRACKED 3
#define LAST_SCORE_ID 2
#define LEADERBOARD_HEADER "LEADERBOARD"
#define MAX_SCORE_LENGTH 5
#define LEADERBOARD_FORMAT "%s  %d"
#define NEW_SCORE_HEADER "NEW HIGHSCORE!"
#define ENTER_NAME "Enter your name"
#define LEADERBOARD_EXTRA_MEMORY 20
#define HIGHSCORE_SIZE 60
#define NO_NAME_ENTERED "Anon"

typedef struct Leaderboard{
    int nameLength;
    char *name;
    int score;
}Leaderboard;

// function that returns a pointer o a leaderboard it just read
Leaderboard* readLeaderboardFromFile(const char *fileName);

// writes leaderboard to a file
void writeLeaderboard(const char *fileName, Leaderboard *leaderboard);

// renders the leaderboard
void renderLeaderboard(Leaderboard *leaderboard, SDL_Renderer *renderer, TTF_Font *font);

// updates the leaderboard
void updateLeaderboard(Leaderboard *leaderboard, int newScore, SDL_Renderer *renderer, TTF_Font *font);

// sort the leaderboard
void sortLeaderboard(Leaderboard *leaderboard);

// renders NEW HIGHSCORE screen
void renderNewHScore(SDL_Renderer *renderer, TTF_Font *font);

// frees the leaderboard
void freeLeaderboard(Leaderboard *leaderboard);

#endif // LEADERBOARD_H_INCLUDED
