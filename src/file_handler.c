#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define PATH_SEP '\\'
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
    #define PATH_SEP '/'
#else
    #include <limits.h>
    #define PATH_SEP '/'
#endif

// Get absolute path to data file
void get_data_file_path(const char *filename, char *full_path, size_t size) {
#if defined(_WIN32) || defined(_WIN64)
    char exe_path[MAX_PATH];
    GetModuleFileName(NULL, exe_path, MAX_PATH);
    char *last_sep = strrchr(exe_path, PATH_SEP);
    if (last_sep) *last_sep = '\0';
    snprintf(full_path, size, "%s\\data\\%s", exe_path, filename);

#elif defined(__APPLE__)
    char exe_path[1024];
    uint32_t bufsize = sizeof(exe_path);
    if (_NSGetExecutablePath(exe_path, &bufsize) != 0) {
        fprintf(stderr, "Buffer too small; need size %u\n", bufsize);
        exit(EXIT_FAILURE);
    }
    char *last_sep = strrchr(exe_path, PATH_SEP);
    if (last_sep) *last_sep = '\0';
    snprintf(full_path, size, "%s/data/%s", exe_path, filename);

#else // Linux
    char exe_path[1024];
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
    if (len == -1) {
        perror("readlink");
        exit(EXIT_FAILURE);
    }
    exe_path[len] = '\0';
    char *last_sep = strrchr(exe_path, PATH_SEP);
    if (last_sep) *last_sep = '\0';
    snprintf(full_path, size, "%s/data/%s", exe_path, filename);
#endif
}

// Save practice text (overwrite file)
void save_practice_data(const char* text) {
    char path[1024];
    get_data_file_path("practice_data.txt", path, sizeof(path));

    FILE *fp = fopen(path, "w");
    if (!fp) {
        perror("Error opening practice_data.txt for writing");
        return;
    }
    fprintf(fp, "%s", text);
    fclose(fp);
}

// Load data from file into 2D array
int load_data(const char* filename, char data[][256], int max_lines) {
    char path[1024];
    get_data_file_path(filename, path, sizeof(path));

    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("Error opening file for reading");
        return -1;
    }

    int count = 0;
    char line[256];
    while (count < max_lines && fgets(line, sizeof(line), fp)) {
        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';

        // Skip comment lines (#) or blank lines
        if (line[0] == '#' || line[0] == '\0') continue;

        strncpy(data[count], line, 256);
        data[count][255] = '\0'; // ensure null-termination
        count++;
    }

    fclose(fp);
    return count;
}

//Saving Score for each mode
void save_practice_score(const char* username, float accuracy, int time_sec, const char* date) {
    char path[1024];
    get_data_file_path("practice_scores.txt", path, sizeof(path));

    FILE *fp = fopen(path, "a");
    if (!fp) { perror("Error saving practice score"); return; }
    fprintf(fp, "%-10s  %6.2f%%  %02d:%02d  %s\n",
            username, accuracy, time_sec / 60, time_sec % 60, date);
    fclose(fp);
}

void save_normal_score(const char* username, int level, float wpm, float accuracy, int time_sec, const char* date) {
    char path[1024];
    get_data_file_path("normal_scores.txt", path, sizeof(path));

    FILE *fp = fopen(path, "a");
    if (!fp) { perror("Error saving normal score"); return; }
    fprintf(fp, "%-10s  %3d  %6.2f  %6.2f%%  %02d:%02d  %s\n",
            username, level, wpm, accuracy, time_sec / 60, time_sec % 60, date);
    fclose(fp);
}

void save_challenge_score(const char* username, int level, float wpm, int time_sec, const char* date) {
    char path[1024];
    get_data_file_path("challenge_scores.txt", path, sizeof(path));

    FILE *fp = fopen(path, "a");
    if (!fp) { perror("Error saving challenge score"); return; }
    fprintf(fp, "%-10s  %3d  %6.2f  %02d:%02d  %s\n",
            username, level, wpm, time_sec / 60, time_sec % 60, date);
    fclose(fp);
}

// Cross-platform getch()
int getch(void) {
#if defined(_WIN32) || defined(_WIN64)
    return _getch();
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}