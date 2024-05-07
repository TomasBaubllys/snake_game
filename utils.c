// SNAKE GAME written using SDL2 and SDL2_ttf libraries
// by Tomas Baublys
// font used: "SummerDreamSans" by Letterhend Studio
// compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
// version 2.0, last modified 1/25/2024

// Contains of the file:
// Definitions of the functions declared in utils.h

#include "include\game.h"

static time_t execStart;

int randPixel(int size, int start){
    return start + (rand() % (size - start + 1));
}

void printFPS(Uint32 *endTime, Uint32 *startTime){
    static int fpsCounter = 0;
    *endTime = SDL_GetTicks();
    fpsCounter++;
    if((*endTime) - (*startTime) >= ONE_SECOND){
        printf(FPS_FORMAT, fpsCounter);
        (*startTime) = SDL_GetTicks();
        fpsCounter = 0;
    }
}

bool endsInBin(char *string){
    unsigned length = strlen(string);
    if(string[length - 1] != 'n' && string[length - 2] != 'i' && string[length - 3] != 'b' && string[length - 4] != '.'){
        return false;
    }
    return true;
}

char** readFiles(const char *path, short *counter){
    char **filesInPath = NULL;
    *counter = 0;
    struct dirent *dp;
    DIR *dir = opendir(path);
    if(!dir){
        return NULL;
    }

    while((dp = readdir(dir)) != NULL){
        if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, SCORES_FOLDER) != 0){
            filesInPath = realloc(filesInPath, sizeof(char*) * ((*counter) + 1));
            if(!filesInPath){
                return NULL;
            }

            filesInPath[*counter] = malloc(strlen(dp->d_name) + 1);
            if(!filesInPath[*counter]){
                return NULL;
            }

            strcpy(filesInPath[*counter], dp->d_name);
            ++(*counter);
        }
    }
    closedir(dir);
    return filesInPath;
}

void logStart(void){
    FILE *sPtr = fopen(LOG_FILE, "a+");
    if(!sPtr){
        sPtr = fopen(LOG_FILE, "w");
        if(!sPtr){
            return;
        }
    }

    execStart = time(NULL);
    struct tm *startTime = localtime(&execStart);

    fprintf(sPtr, LOGGER_START_FORMAT, asctime(startTime));

    fclose(sPtr);
}

void logEnd(void){
    FILE *ePtr = fopen(LOG_FILE, "a+");
    if(!ePtr){
        ePtr = fopen(LOG_FILE, "w");
        if(!ePtr){
            return;
        }
    }

    time_t execEnd = time(NULL);
    struct tm* endTime = localtime(&execEnd);
    fprintf(ePtr, LOGGER_ENDING_FORMAT, asctime(endTime));
    fprintf(ePtr, LOGGER_ELAPSED_FORMAT, execEnd - execStart);

    fclose(ePtr);
}

char* addDotBin(char *str){
    if(!str){
        return NULL;
    }

    return strcat(str, BINARY_FILE);
}

char *noNameEntered(void){
    char *str = (char*)calloc(sizeof(char), strlen(NO_NAME_ENTERED) + 1);
    if(!str){
        return NULL;
    }

    strcpy(str, NO_NAME_ENTERED);
    return str;
}
