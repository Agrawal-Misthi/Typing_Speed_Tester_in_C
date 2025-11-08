#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <time.h>

// Max length constants
#define MAX_NAME 50

// Structures for each mode
typedef struct {
    char name[MAX_NAME];
    float accuracy;
    int total_seconds;
    char date[20];  // YYYY-MM-DD
} PracticeScore;

typedef struct {
    char name[MAX_NAME];
    int level;
    float wpm;
    float accuracy;
    int total_seconds;
    char date[20];
} NormalScore;

typedef struct {
    char name[MAX_NAME];
    int level;
    float wpm;
    int total_seconds;
    char date[20];
} ChallengeScore;
#ifdef __cplusplus              // 🟢 ADD — begin C++ protection
extern "C" {
#endif


void display_practice_scores();
void display_normal_scores();
void display_challenge_scores();

#ifdef __cplusplus
}
#endif

#endif
