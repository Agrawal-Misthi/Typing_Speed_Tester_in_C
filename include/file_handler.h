#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>   // for _getch()
#else
    #include <termios.h>
    #include <unistd.h>
#endif

// 👇👇👇 ADD THESE TWO LINES
#ifdef __cplusplus
extern "C" {
#endif

// ------------------------- File Handling -------------------------

// Get absolute path to a file inside the data folder
void get_data_file_path(const char *filename, char *full_path, size_t size);

// Load multiple lines from a file into a 2D array of strings
// Returns number of lines read or -1 on error; ignores lines starting with '#' or blank lines
int load_data(const char* filename, char data[][256], int max_lines);

// Save practice text (overwrite practice_data.txt)
void save_practice_data(const char* text);

// ------------------------- Score Saving -------------------------

// Save scores for different modes (date provided by caller)
void save_practice_score(const char* username, float accuracy, int total_seconds, const char* date);
void save_normal_score(const char* username, int level, float wpm, float accuracy, int total_seconds, const char* date);
void save_challenge_score(const char* username, int level, float wpm, int total_seconds, const char* date);

// ------------------------- Utility -------------------------

// Cross-platform getch() for single-character input
int getch(void);

// 👇👇👇 AND THESE TWO LINES AT THE END
#ifdef __cplusplus
}
#endif

#endif // FILE_HANDLER_H
