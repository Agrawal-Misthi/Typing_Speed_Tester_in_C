#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scoreboard.h"
#include "file_handler.h"

#define MAX_WORDS 1000
#define MAX_INPUT_LEN 256
#define MAX_MISTAKES 5
#define EXTRA_TIME 10  // seconds added per correct word/phrase

// Fisher–Yates (Knuth) Shuffle
// Safe Fisher–Yates shuffle with bounds checks + debug
void shuffle_lines(char arr[][MAX_INPUT_LEN], int n) {
    if (n <= 1) return;

    srand((unsigned int)time(NULL));

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // Basic sanity checks
        if (i < 0 || i >= n || j < 0 || j >= n) {
            fprintf(stderr, "shuffle_lines: index out of range i=%d j=%d n=%d\n", i, j, n);
            return;
        }

        size_t len_i = strnlen(arr[i], MAX_INPUT_LEN);
        size_t len_j = strnlen(arr[j], MAX_INPUT_LEN);

        // If either string exactly fills the buffer without a NUL, that's suspicious
        if (len_i >= (size_t)MAX_INPUT_LEN - 1 || len_j >= (size_t)MAX_INPUT_LEN - 1) {
            fprintf(stderr, "shuffle_lines: suspicious long line (i=%d len=%zu, j=%d len=%zu). Aborting shuffle.\n",
                    i, len_i, j, len_j);
            return;
        }

        // Temporary buffer on heap (avoid big stack usage)
        char *temp = (char *)malloc(MAX_INPUT_LEN);
        if (!temp) {
            perror("shuffle_lines: malloc");
            return;
        }

        // Safe copies with explicit NUL termination
        memcpy(temp, arr[i], len_i + 1);          // include NUL
        memset(arr[i] + len_j, 0, 1);             // ensure arr[i] has NUL at correct place (just defensive)
        memmove(arr[i], arr[j], len_j + 1);
        memmove(arr[j], temp, len_i + 1);

        // Ensure both are NUL-terminated (extra safety)
        arr[i][MAX_INPUT_LEN - 1] = '\0';
        arr[j][MAX_INPUT_LEN - 1] = '\0';

        free(temp);
    }
}


void normal_mode() {
    char username[50];
    char words[MAX_WORDS][MAX_INPUT_LEN];
    int words_count;
    int level = 0;
    int mistakes = 0;
    int total_chars_typed = 0;
    int correct_chars = 0;
    float wpm = 0.0;

    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    // Load words/phrases/sentences
    words_count = load_data("default_data.txt", words, MAX_WORDS);
    if (words_count <= 0) {
        printf("No words loaded for normal mode. Please check data file.\n");
        return;
    }

    shuffle_lines(words, words_count);
    //yo

    time_t start_time = time(NULL);
    int time_limit = 60;  // base time in seconds

    while (mistakes < MAX_MISTAKES && level < words_count) {
        if (level >= words_count || words[level][0] == '\0') {
            printf("⚠️ Invalid level %d or empty line\n", level);
            break;
        }

        char *expected = words[level];
        size_t len = strlen(expected);
        char input[MAX_INPUT_LEN] = {0};
                  int h = time_limit / 3600;
                 int m = (time_limit % 3600) / 60;
                 int s = time_limit % 60;
                 printf("\rTime Left: %02d:%02d:%02d ", h, m, s);
                 printf("\nLevel %d | \rTime Left: %02d:%02d:%02d  | Lifelines left: %d\n",
              level + 1, h, m, s, MAX_MISTAKES - mistakes);
                 fflush(stdout);
        printf("Type this: %s\n", expected);
        printf("Start typing: ");

        time_t word_start = time(NULL);
        int mistake_in_word = 0;

        for (size_t i = 0; i < len; i++) {
            char ch = getch();
            putchar(ch); // show typed char
            input[i] = ch;
            total_chars_typed++;

            if (ch != expected[i]) {
                mistake_in_word = 1;
                mistakes++;
                printf("\n❌ Wrong character! Total mistakes: %d\n", mistakes);
                break;
            } else {
                correct_chars++;
            }
        }

        time_t word_end = time(NULL);
        int elapsed = (int)difftime(word_end, word_start);
        time_limit -= elapsed;  // decrease remaining time

        if (!mistake_in_word) {
            printf("\n✅ Correct!\n");
            level++;
            time_limit += EXTRA_TIME; // reward extra time
        }

        // Menu after each level
        if (mistakes < MAX_MISTAKES) {
            int choice;
            printf("\nMenu: 1 = Continue | 2 = Quit\nChoice: ");
            scanf("%d%*c", &choice); // consume newline
            if (choice == 2) break;
        }

        if (time_limit <= 0) {
            printf("\n⏰ Time’s up!\n");
            break;
        }
    }

    time_t end_time = time(NULL);
    int total_time = (int)difftime(end_time, start_time);
    if (total_time == 0) total_time = 1;

    wpm = ((float)correct_chars / 5.0f) / ((float)total_time / 60.0f);

    // 🕒 Generate current date
    char date[20];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(date, sizeof(date), "%d-%m-%Y", tm_info);

    // 💾 Save score with date
    save_normal_score(username, level, wpm,
                      ((float)correct_chars / total_chars_typed) * 100.0f,
                      total_time, date);

    printf("\n=== GAME OVER ===\n");
    printf("Levels completed: %d\nMistakes: %d\nTime taken: %d sec\nWPM: %.2f\n",
           level, mistakes, total_time, wpm);

    display_normal_scores();
}