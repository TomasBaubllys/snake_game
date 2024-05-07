// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Declarations of helper functions

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "leaderboard.h"

#define ONE_SECOND 1000
#define BINARY_FILE ".bin"
#define FPS_FORMAT "\rFPS: %d"
#define LOGGER_START_FORMAT "Started: %s"
#define LOGGER_ENDING_FORMAT "Ended: %s"
#define LOGGER_ELAPSED_FORMAT "Time elapsed: %lld seconds\n"

// returns a random number in the given interval
int randPixel(int size, int start);

// calculates and prints current frames per second to the terminal
void printFPS(Uint32 *endTime, Uint32 *startTime);

// checks if a given string ends in .bin
bool endsInBin(char *string);

// reads existent files in the given directory, returns a "double array"
char** readFiles(const char *path, short *counter);

// writes programs starting time to a file log.txt
void logStart(void);

// writes programs ending and elapsed time to log.txts
void logEnd(void);

// adds .bin to a string
char* addDotBin(char *str);

// returns a pointer a string defined by NO_NAME_ENTERED
char *noNameEntered(void);

#endif // UTILS_H_INCLUDED
