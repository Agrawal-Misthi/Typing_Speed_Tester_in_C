#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scoreboard.h"

#define MAX_SCORES 100

// ---------------- Utility ----------------
void get_current_date(char *buffer, size_t size) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, size, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

// ---------------- Practice Mode ----------------
void display_practice_scores() {
    PracticeScore scores[MAX_SCORES];
    int count = 0;

    FILE *fp = fopen("data/practice_score.txt", "r");
    if (!fp) {
        printf("No practice scores found.\n");
        return;
    }

    while (fscanf(fp, "%49s %f %d %19s", 
                  scores[count].name, 
                  &scores[count].accuracy,
                  &scores[count].total_seconds, 
                  scores[count].date) == 4) {
        count++;
        if (count >= MAX_SCORES) break;
    }
    fclose(fp);

    // Sort by accuracy descending
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[j].accuracy > scores[i].accuracy) {
                PracticeScore temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    printf("\n--- Practice Mode Scores ---\n");
    printf("Name\tAccuracy\tTime (mm:ss)\tDate\n");
    for (int i = 0; i < count; i++) {
        int mins = scores[i].total_seconds / 60;
        int secs = scores[i].total_seconds % 60;
        printf("%s\t%.2f%%\t%02d:%02d\t%s\n",
               scores[i].name, scores[i].accuracy, mins, secs, scores[i].date);
    }
}

// ---------------- Normal Mode ----------------
void display_normal_scores() {
    NormalScore scores[MAX_SCORES];
    int count = 0;

    FILE *fp = fopen("data/normal_score.txt", "r");
    if (!fp) {
        printf("No normal mode scores found.\n");
        return;
    }

    while (fscanf(fp, "%49s %d %f %f %d %19s", 
                  scores[count].name, 
                  &scores[count].level,
                  &scores[count].wpm, 
                  &scores[count].accuracy, 
                  &scores[count].total_seconds,
                  scores[count].date) == 6) {
        count++;
        if (count >= MAX_SCORES) break;
    }
    fclose(fp);

    // Sort by WPM descending (and then accuracy)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[j].wpm > scores[i].wpm ||
               (scores[j].wpm == scores[i].wpm && scores[j].accuracy > scores[i].accuracy)) {
                NormalScore temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    printf("\n--- Normal Mode Scores ---\n");
    printf("Name\tLevel\tWPM\tAccuracy\tTime (mm:ss)\tDate\n");
    for (int i = 0; i < count; i++) {
        int mins = scores[i].total_seconds / 60;
        int secs = scores[i].total_seconds % 60;
        printf("%s\t%d\t%.2f\t%.2f%%\t%02d:%02d\t%s\n",
               scores[i].name, scores[i].level, scores[i].wpm, scores[i].accuracy,
               mins, secs, scores[i].date);
    }
}

// ---------------- Challenge Mode ----------------
void display_challenge_scores() {
    ChallengeScore scores[MAX_SCORES];
    int count = 0;

    FILE *fp = fopen("data/challenge_score.txt", "r");
    if (!fp) {
        printf("No challenge scores found.\n");
        return;
    }

    while (fscanf(fp, "%49s %d %f %d %19s", 
                  scores[count].name, 
                  &scores[count].level,
                  &scores[count].wpm, 
                  &scores[count].total_seconds, 
                  scores[count].date) == 5) {
        count++;
        if (count >= MAX_SCORES) break;
    }
    fclose(fp);

    // Sort by WPM descending, then fastest time
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[j].wpm > scores[i].wpm ||
               (scores[j].wpm == scores[i].wpm && scores[j].total_seconds < scores[i].total_seconds)) {
                ChallengeScore temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    printf("\n--- Challenge Mode Scores ---\n");
    printf("Name\tLevel\tWPM\tTime (mm:ss)\tDate\n");
    for (int i = 0; i < count; i++) {
        int mins = scores[i].total_seconds / 60;
        int secs = scores[i].total_seconds % 60;
        printf("%s\t%d\t%.2f\t%02d:%02d\t%s\n",
               scores[i].name, scores[i].level, scores[i].wpm, mins, secs, scores[i].date);
    }
}