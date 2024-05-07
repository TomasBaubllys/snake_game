// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Declarations of most of the functions that are used for the menus logic

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "game.h"

#define START_SIZE 80
#define PRESS_SPACE_SIZE 20
#define SCORE_SIZE 20
#define SCORE_MARGIN 10
#define SCORE_LENGTH 10
#define LINE_WIDTH 5
#define LINE_MARGIN 10
#define GAME_OVER_SIZE 80
#define HSCORE_SIZE 16
#define PRESS_TAB_SIZE 15
#define PRESS_TAB_MARGIN 10
#define CONTROLS_SIZE 20
#define CONTROLS_MARGIN 20
#define SAVE_GAMESIZE 20
#define CHOOSING_POINT_SIZE 10
#define CHOOSING_POINT_MARGIN 7
#define MAX_SAVEGAMES 14
#define CENTERED true
#define UNCENTERED false

#define SNAKE "SNAKE"
#define SPACE_TO_START "PRESS SPACE TO START"
#define TAB_FOR_CONTROLS "PRESS TAB FOR CONTROLS"
#define NEW_SAVEGAME_HEADER "ENTER THE SAVEGAMES NAME"
#define PRESS_SPACE_C_MSG "PRESS SPACE TO CONTINUE"
#define NO_SAVE_GAMES_MSG "NO SAVE GAMES FOUND"

#define CONTROLS_MSG_1 "W A S D - MOVE"
#define CONTROLS_MSG_2 "L - LOAD A SAVEGAME GAME"
#define CONTROLS_MSG_3 "F - TOGGLE FULLSCREEN ON/OFF"
#define CONTROLS_MSG_4 "ESC - EXIT TO MAIN MENU"
#define CONTROLS_MSG_5 "SHIFT - SAVE CURRENT GAME"
#define CONTROLS_MSG_6 "ENTER - SELECT A SAVEGAME"
#define CONTROLS_MSG_7 "DELETE - DELETE A SAVEGAME"
#define CONTROLS_MSG_8 "Q - QUIT"
#define CONTROLS_MSG_9 "R - SECRET GAMEMODE"
#define CONTROLS_MSG_10 "B - LEADERBOARD"
#define CONTROLS_MSG_COUNT 10

#define NEW "NEW"

#define SCORE_FORMAT "SCORE : %u"
#define HIGHSCORE_FORMAT "HIGHSCORE : %d"

#define LOAD_GAME_MSG "AVAILABLE SAVEGAMES"
#define SAVE_GAME_MSG "SAVE CURRENT GAME"

#define GAME_OVER_MSG "GAME OVER"

// colour used for all objects & text
extern SDL_Color green;

// iniatializes the font (opens it)
bool initFont(TTF_Font **font);

// renders the main menu
bool renderMenu(SDL_Renderer *renderer, TTF_Font *font);

// renders current games score to the top left
void renderScore(unsigned score, SDL_Renderer *renderer, TTF_Font *font);

// renders GAME OVER screen
void renderGameOver(unsigned score, SDL_Renderer *renderer, TTF_Font *font, bool radaviciusMode);

// renders all time highest score to the top right
void renderHscore(SDL_Renderer *renderer, int hScore, TTF_Font *font);

// renders the controls menu
bool renderControls(SDL_Renderer *renderer, TTF_Font *font);

// renders both the save and load game menus
char* renderLoadSave(SDL_Renderer *renderer, TTF_Font *font, const char *header, bool loadSave);

// renders a screen where the user can enter a files name
char* renderInputString(SDL_Renderer *renderer, TTF_Font *font, const char *header);

// renders any text to the given position
bool renderTextSolid(SDL_Renderer *renderer, TTF_Font *font, const char *str, unsigned fontSize, unsigned xPos, unsigned yPos, bool centered);

// renders the upper line on the screen
void renderUpperLine(SDL_Renderer *renderer);

#endif // MENU_H_INCLUDED
