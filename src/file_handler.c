#include <stdio.h>
#include <string.h>
#include "file_handler.h"

void save_practice_data(const char* text) {
    FILE *fp = fopen("practice_data.txt", "w");
    if (!fp) {
        perror("Error opening practice_data.txt for writing");
        return;
    }
    fprintf(fp, "%s", text);
    fclose(fp);
}

int load_data(const char* filename, char data[][256], int max_lines) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file for reading");
        return -1;
    }

    int count = 0;
    while (count < max_lines && fgets(data[count], 256, fp)) {
        size_t len = strlen(data[count]);
        if (len > 0 && data[count][len - 1] == '\n') {
            data[count][len - 1] = '\0'; // Remove newline
        }
        count++;
    }

    fclose(fp);
    return count;
}

void save_score(const char* username, int time_taken, int level, float wpm) {
    FILE *fp = fopen("scoreboard.txt", "a"); // Append mode
    if (!fp) {
        perror("Error opening scoreboard.txt for appending");
        return;
    }
    // Format: username time_taken level wpm
    fprintf(fp, "%s %d %d %.2f\n", username, time_taken, level, wpm);
    fclose(fp);
}