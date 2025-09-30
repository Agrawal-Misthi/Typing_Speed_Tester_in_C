//header file to declares two functions which save and load text to/from files.

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

// Save practice text (overwrite fixed file)
void save_practice_data(const char* text);

// Load multiple lines from a file into a 2D array of strings
// Returns number of lines read or -1 on error
int load_data(const char* filename, char data[][256], int max_lines);

// Append a score record to the scoreboard file
void save_score(const char* username, int time_taken, int level, float wpm);

#endif // FILE_HANDLER_H