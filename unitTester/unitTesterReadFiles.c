#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>

#define SCORES_FOLDER_TEST "scores"

// function to test
char** readFiles(const char *path, short *counter){
    char **filesInPath = NULL;
    *counter = 0;
    struct dirent *dp;
    DIR *dir = opendir(path);
    if(!dir){
        return NULL;
    }
    while((dp = readdir(dir)) != NULL){
        if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, SCORES_FOLDER_TEST) != 0){
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
// function to test

// checks if all of the files have been read correctly
bool areFilesMatching(const char *files[], int realCounter);

// frees the read directory
void freeReadFiles(char *files[], short counter);

int main(void){

    const char *currentFiles[] = {"unitTesterReadFiles.c", "unitTesterReadFiles.exe", "unitTesterReadFiles.o", "unitTesterAddCell.c", "unitTesterSortLeader.c"};
    short realCounter = 5;
    assert(areFilesMatching(currentFiles, realCounter));

    return 0;
}


bool areFilesMatching(const char *files[], int realCounter){
    short counter = 0;
    char **readDir = readFiles("C:\\Users\\tomas\\Desktop\\SnakeV1\\unitTester", &counter);

    if(counter != realCounter){
        return false;
    }

    bool fileFound = false;;
    for(int i = 0; i < counter; ++i){
        fileFound = false;

        for(int j = 0; j < realCounter; ++j){
            if(strcmp(files[j], readDir[i])){
                fileFound = true;
            }
        }

        if(!fileFound){
            freeReadFiles(readDir, i);
            return false;
        }

    }

    freeReadFiles(readDir, counter);
    return true;
}

void freeReadFiles(char *files[], short counter){
    for(int i = 0; i < counter; ++i){
        free(i[files]);
    }
    free(files);
}
