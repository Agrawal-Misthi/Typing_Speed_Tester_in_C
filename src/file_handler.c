#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define PATH_SEP '\\'
#else
    #include <unistd.h>
    #include <limits.h>
    #define PATH_SEP '/'
#endif

#if defined(__APPLE__)
    #include <mach-o/dyld.h>
#elif defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// Get absolute path to data file
void get_data_file_path(const char *filename, char *full_path, size_t size) {
#if defined(_WIN32) || defined(_WIN64)
    char exe_path[MAX_PATH];
    GetModuleFileName(NULL, exe_path, MAX_PATH);
    char *last_sep = strrchr(exe_path, '\\');
    if (last_sep) *last_sep = '\0';
    snprintf(full_path, size, "%s\\data\\%s", exe_path, filename);

#elif defined(__APPLE__)
    char exe_path[1024];
    uint32_t bufsize = sizeof(exe_path);
    if (_NSGetExecutablePath(exe_path, &bufsize) != 0) {
        fprintf(stderr, "Buffer too small; need size %u\n", bufsize);
        exit(EXIT_FAILURE);
    }
    char *last_sep = strrchr(exe_path, '/');
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
    char *last_sep = strrchr(exe_path, '/');
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
    char path[1000];
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

        // Skip comment lines (#) or completely blank lines
        if (line[0] == '#' || line[0] == '\0') continue;

        // Copy valid line into data array
        strncpy(data[count], line, 256);
        data[count][255] = '\0'; // ensure null-termination
        count++;
    }

    fclose(fp);
    return count;
}

// Append a score record to scoreboard.txt in project root
void save_score(const char* username, int time_taken, int level, float wpm) {
    FILE *fp = fopen("scoreboard.txt", "a");
    if (!fp) {
        perror("Error opening scoreboard.txt for appending");
        return;
    }

    fprintf(fp, "%s %d %d %.2f\n", username, time_taken, level, wpm);
    fclose(fp);
}