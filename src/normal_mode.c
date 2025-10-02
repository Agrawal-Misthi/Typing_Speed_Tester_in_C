#include <stdio.h>
#include <string.h>
#include <time.h>
#include "file_handler.h"

#define MAX_WORDS 1000
#define MAX_INPUT 256
#define MAX_MISTAKES 5

//Fisher–Yates (Knuth) Shuffle
void shuffle_lines(char arr[][MAX_INPUT], int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp[MAX_INPUT];
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[j]);
        strcpy(arr[j], temp);
    }
}

void normal_mode() {
    char username[50];
    char words[MAX_WORDS][256];
    int words_count;
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

    // Shuffle word list
    shuffle_lines(words, words_count);
    //yo

    // Timer setup
    time_t start_time = time(NULL);
    int time_limit = 60;  // base time

    // Gameplay loop
    while (mistakes < MAX_MISTAKES && level < words_count) {
        char user_input[MAX_INPUT];

        printf("\nLevel %d | Time left: %d sec | Lifelines left: %d\n",
               level + 1, time_limit - (int)(time(NULL) - start_time), MAX_MISTAKES - mistakes);
        printf("Type this: %s\n", words[level]);

        fgets(user_input, sizeof(user_input), stdin);
        user_input[strcspn(user_input, "\n")] = '\0'; // remove newline

        if (strcmp(user_input, words[level]) == 0) {
            printf("✅ Correct!\n");
            level++;
            time_limit += 10; // reward with 10 sec
        } else {
            printf("❌ Wrong! You typed: %s\n", user_input);
            mistakes++;
        }

        // Check if time is over
        if ((int)(time(NULL) - start_time) >= time_limit) {
            printf("\n⏰ Time’s up!\n");
            break;
        }
    }

    // Calculate WPM
    int total_time = (int)(time(NULL) - start_time);
    if (total_time == 0) total_time = 1; // prevent divide by zero
    wpm = (float)level / ((float)total_time / 60.0f);

    // Save scoreboard
    save_score(username, total_time, level, wpm);

    printf("\n=== GAME OVER ===\n");
    printf("Levels completed: %d\nMistakes: %d\nTime taken: %d sec\nWPM: %.2f\n",
           level, mistakes, total_time, wpm);
}