#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#define MAX_SCORES 100

// ---------------- Score Structs ----------------
typedef struct {
    char name[50];
    float accuracy;
    int total_seconds;
    char date[20];
} PracticeScore;

typedef struct {
    char name[50];
    int level;
    float wpm;
    float accuracy;
    int total_seconds;
    char date[20];
} NormalScore;

typedef struct {
    char name[50];
    int level;
    float wpm;
    int total_seconds;
    char date[20];
} ChallengeScore;

// ---------------- Plain Text Display ----------------
void display_practice_scores();
void display_normal_scores();
void display_challenge_scores();

// ---------------- HTML Display for Web ----------------
void display_practice_scores_html();
void display_normal_scores_html();
void display_challenge_scores_html();

// ---------------- Utility ----------------
void get_current_date(char *buffer, size_t size);

#ifdef __cplusplus
}
#endif

#endif
