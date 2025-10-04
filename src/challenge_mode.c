#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "file_handler.h"
#include "scoreboard.h"

#define MAX_WORDS 1000
#define MAX_INPUT_LEN 256   // renamed

void challenge_mode() {
    char username[50];
    char words[MAX_WORDS][MAX_INPUT_LEN];
    int words_count;
    int level = 0;
    float wpm = 0.0;
    int total_chars_typed = 0;

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    words_count = load_data("data/normal_mode_words.txt", words, MAX_WORDS);
    if (words_count < 1) {
        printf("No challenge data found. Please check data file.\n");
        return;
    }

    printf("\n--- Challenge Mode ---\n");
    printf("Type the words/phrases exactly. One mistake ends the game!\n\n");

    time_t start_time = time(NULL);
    time_t end_time;  // <-- declare before label

    for (level = 0; level < words_count; level++) {
        char *expected = words[level];
        size_t len = strlen(expected);
        char input[MAX_INPUT_LEN] = {0};

        printf("Level %d: %s\n", level + 1, expected);
        printf("Start typing: ");

        for (size_t i = 0; i < len; i++) {
            char ch = getch();
            putchar(ch);
            if (ch != expected[i]) {
                printf("\n❌ Mistake! Game Over.\n");
                goto end_game;
            }
            input[i] = ch;
            total_chars_typed++;
        }

        printf("\n✅ Correct!\n\n");
    }

end_game:
    end_time = time(NULL);  // <-- assign here
    int total_seconds = (int)difftime(end_time, start_time);
    if (total_seconds == 0) total_seconds = 1;

    wpm = ((float)total_chars_typed / 5.0f) / ((float)total_seconds / 60.0f);

    char date[20];
    struct tm *tm_info = localtime(&end_time);
    strftime(date, sizeof(date), "%d-%m-%Y", tm_info);

    save_challenge_score(username, level, wpm, total_seconds, date);

    printf("\n--- Challenge Over ---\n");
    printf("Player: %s\nLevels Completed: %d\nWPM: %.2f\nTime: %d min %d sec\n",
           username, level, wpm, total_seconds / 60, total_seconds % 60);

    printf("\n🏆 Challenge Mode Leaderboard 🏆\n");
    display_challenge_scores();
}