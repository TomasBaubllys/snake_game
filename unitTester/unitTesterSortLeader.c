#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define LEADERBOARD_TEST_NAME "EMPTY"
#define MAX_H_SCORE_TEST 200
#define MAX_SCORES_TRACKED_TEST 10

typedef struct Leaderboard{
    int nameLength;
    char *name;
    int score;
}Leaderboard;

// function to test
void sortLeaderboard(Leaderboard *leaderboard){
    for(int i = 0; i < MAX_SCORES_TRACKED_TEST; ++i){
        for(int j = 0; j < MAX_SCORES_TRACKED_TEST - i - 1; ++j){
            if(leaderboard[j].score < leaderboard[j + 1].score){
                Leaderboard tempLead = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = tempLead;
            }
        }
    }
}
// function to test

// testing if the leaderboard is sorted correctly
bool isLeaderBoardSorted(Leaderboard *leaderboard);

// fills leaderboard with random numbers;
Leaderboard* createLeaderboardRand(void);

// prints out the leaderboard
void printLeaderboard(Leaderboard *Leaderboard);

int main(void){
    srand(time(NULL));

    Leaderboard *testLead = createLeaderboardRand();
    assert(isLeaderBoardSorted(testLead));
    printLeaderboard(testLead);

    for(int i = 0 ; i < MAX_SCORES_TRACKED_TEST; ++i){
        free(testLead[i].name);
    }
    free(testLead);
    return 0;
}

bool isLeaderBoardSorted(Leaderboard *leaderboard){
    sortLeaderboard(leaderboard);

    for(int i = 0; i < MAX_SCORES_TRACKED_TEST - 1; ++i){
        if(leaderboard[i].score < leaderboard[i + 1].score){
            return false;
        }
    }

    return true;
}

Leaderboard* createLeaderboardRand(void){
    Leaderboard *leaderboard = calloc(sizeof(Leaderboard), MAX_SCORES_TRACKED_TEST);
    if(!leaderboard){
        return NULL;
    }

    for(int i = 0; i < MAX_SCORES_TRACKED_TEST; ++i){
        leaderboard[i].name = calloc(sizeof(char), strlen(LEADERBOARD_TEST_NAME) + 1);
        strcpy(leaderboard[i].name, LEADERBOARD_TEST_NAME);
        leaderboard[i].nameLength = strlen(LEADERBOARD_TEST_NAME);
        leaderboard[i].score = rand() % MAX_H_SCORE_TEST;
    }

    return leaderboard;
}

void printLeaderboard(Leaderboard *leaderboard){
    for(int i = 0 ; i < MAX_SCORES_TRACKED_TEST; ++i){
        printf("%s  %d\n", leaderboard[i].name, leaderboard[i].score);
    }
}
