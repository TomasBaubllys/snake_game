// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Most of the main GAMES declarations + declaration of a game status initialization function

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "utils.h"
#include <dirent.h>
#include <time.h>
#include <string.h>

#define WIDTH 640
#define HEIGTH 480
#define DELAY 16
#define MAX_FILE_LENGTH 50
#define MAX_FILE_NAME 31
#define DATA 10
#define MAX_LINE_LENGTH 40
#define LOAD true
#define SAVE false

#define FONT "fonts\\SummerDreamSans.ttf"

#define BACKROUND_C_R 199
#define BACKROUND_C_G 244
#define BACKROUND_C_B 216
#define BACKROUND_C_A 255

#define OBJECT_C_R 67
#define OBJECT_C_G 82
#define OBJECT_C_B 61
#define OBJECT_C_A 255

#define WINDOW_NAME "snake"

#define LOG_FILE "log.txt"
#define LEADERBOARD_FILE "data\\scores\\leaderboard.bin"
#define SCORES_FOLDER "scores"
#define STUDENTS_FOLDER "textures\\students"
#define STUDENTS_DIR "textures\\students\\%s"
#define TEXTURES_DIR "textures\\%s"
#define RADAVICIUS_TEX "textures\\radavicius.bmp"
#define GAME_OVER_TEX "textures\\gameover.bmp"
#define DATA_FOLDER "data"
#define DATA_DIR "data\\%s"
#define INIT_ERROR "Initialization error!"
#define FONT_INIT_ERROR "Font initialization error!"

typedef struct GameStatus{
    bool started;
    bool gameOver;
    bool run;
    bool saved;
    bool tabPressed;
    bool fullscreen;
    bool leaderb;
    bool leaderbUpdated;
}GameStatus;

// initializes the starting game status
GameStatus* initGameStatus(void);

#endif // GAME_H_INCLUDED
