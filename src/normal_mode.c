#include <stdio.h>
#include "file_handler.h"

#define MAX_WORDS 1000

void normal_mode() {
    char username[50];
    char words[MAX_WORDS][256];
    int words_count;
    int time_taken = 60; // starting timer (seconds)
    int level = 0;
    int mistakes = 0;
    float wpm = 0.0;

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    // Remove trailing newline from username
    username[strcspn(username, "\n")] = '\0';

    // Load words for practice (replace with your actual data file)
    words_count = load_data("normal_mode_words.txt", words, MAX_WORDS);
    if (words_count < 1) {
        printf("No words loaded for normal mode. Please check data file.\n");
        return;
    }

    // Example loop for levels (simplified)
    while (mistakes < 5 && level < words_count) {
        printf("Type this word: %s\n", words[level]);
        // Add your timing, input, and mistake logic here...

        level++;
        time_taken += 10;  // Add 10 seconds per level as per your rules
    }

    // Calculate WPM (simplified example)
    wpm = (float)level / ((float)time_taken / 60.0f);

    // Save scoreboard data
    save_score(username, time_taken, level, wpm);

    printf("Game Over! Levels completed: %d, Time taken: %d seconds, WPM: %.2f\n",
           level, time_taken, wpm);
}
