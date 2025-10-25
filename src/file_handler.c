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

// ------------------------- File Handling -------------------------

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

    // Resolve to absolute path
    char resolved_path[1024];
    realpath(exe_path, resolved_path);

    // Trim the executable name
    char *last_sep = strrchr(resolved_path, '/');
    if (last_sep) *last_sep = '\0';

    // If running from src/, move up one directory
    if (strstr(resolved_path, "/src")) {
        snprintf(full_path, size, "%s/../data/%s", resolved_path, filename);
    } else {
        snprintf(full_path, size, "%s/data/%s", resolved_path, filename);
    }

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
        line[strcspn(line, "\n")] = '\0'; // remove newline
        if (line[0] == '#' || line[0] == '\0') continue; // skip comments/blank
        strncpy(data[count], line, 256);
        data[count][255] = '\0';
        count++;
    }

    fclose(fp);
    return count;
}

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

// ------------------------- Score Saving -------------------------

void save_practice_score(const char* username, float accuracy, int total_seconds, const char* date) {
    char path[1024];
    get_data_file_path("practice_score.txt", path, sizeof(path));

    FILE *fp = fopen(path, "a");
    if (!fp) { perror("Error saving practice score"); return; }
    fprintf(fp, "%-10s %.2f %d %s\n", username, accuracy, total_seconds, date);
    fclose(fp);
}

void save_normal_score(const char* username, int level, float wpm, float accuracy, int total_seconds, const char* date) {
    char path[1024];
    get_data_file_path("normal_score.txt", path, sizeof(path));

    FILE *fp = fopen(path, "a");
    if (!fp) { perror("Error saving normal score"); return; }
    fprintf(fp, "%-10s %3d %.2f %.2f %d %s\n", username, level, wpm, accuracy, total_seconds, date);
    fclose(fp);
}

void save_challenge_score(const char* username, int level, float wpm, int total_seconds, const char* date) {
    char path[1024];
    get_data_file_path("challenge_score.txt", path, sizeof(path));

    FILE *fp = fopen(path, "a");
    if (!fp) { perror("Error saving challenge score"); return; }
    fprintf(fp, "%-10s %3d %.2f %d %s\n", username, level, wpm, total_seconds, date);
    fclose(fp);
}

// ------------------------- Utility -------------------------

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
