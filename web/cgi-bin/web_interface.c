#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../include/file_handler.h"
#include "../../include/modes.h"
#include "../../include/scoreboard.h"

#define MAX_INPUT 8192

// Helper to decode URL-encoded text
void url_decode(char *src, char *dest) {
    char a, b;
    while (*src) {
        if ((*src == '%') &&
            ((a = src[1]) && (b = src[2])) &&
            (isxdigit(a) && isxdigit(b))) {
            if (a >= 'a') a -= 'a' - 'A';
            if (a >= 'A') a -= ('A' - 10);
            else a -= '0';
            if (b >= 'a') b -= 'a' - 'A';
            if (b >= 'A') b -= ('A' - 10);
            else b -= '0';
            *dest++ = 16 * a + b;
            src += 3;
        } else if (*src == '+') {
            *dest++ = ' ';
            src++;
        } else {
            *dest++ = *src++;
        }
    }
    *dest = '\0';
}

// Extract "username" from QUERY_STRING
void get_username(char *username, size_t size) {
    char *query = getenv("QUERY_STRING");
    if (!query || strlen(query) == 0) {
        snprintf(username, size, "Guest");
        return;
    }
    char *start = strstr(query, "username=");
    if (!start) {
        snprintf(username, size, "Guest");
        return;
    }
    start += 9; // skip "username="
    url_decode(start, username);
}

// Read POST data from stdin
void get_post_data(char *buffer, size_t size) {
    char *len_str = getenv("CONTENT_LENGTH");
    if (!len_str) { buffer[0] = '\0'; return; }

    int len = atoi(len_str);
    if (len <= 0 || len >= size) { buffer[0] = '\0'; return; }

    fread(buffer, 1, len, stdin);
    buffer[len] = '\0';
}

int main(void) {
    printf("Content-type:text/html\n\n");

    char username[100];
    get_username(username, sizeof(username));

    char *request_method = getenv("REQUEST_METHOD");
    char post_data[MAX_INPUT] = {0};

    if (request_method && strcmp(request_method, "POST") == 0) {
        get_post_data(post_data, sizeof(post_data));
        char *mode_start = strstr(post_data, "mode=");
        if (mode_start) {
            mode_start += 5;

            // HTML page wrapper
            printf("<html><head><meta charset='UTF-8'><title>Typing Speed Tester</title></head><body>");

            if (strncmp(mode_start, "start_practice", 14) == 0) {
                practice_mode();
            } 
            else if (strncmp(mode_start, "save_practice", 13) == 0) {
                char *text_start = strstr(post_data, "practice_text=");
                if (text_start) {
                    text_start += 14;
                    char decoded_text[MAX_INPUT];
                    url_decode(text_start, decoded_text);
                    save_practice_data(decoded_text);
                    printf("<p>✅ Practice text saved!</p>");
                }
            }
            else if (strncmp(mode_start, "start_normal", 12) == 0) {
                normal_mode();
            } 
            else if (strncmp(mode_start, "start_challenge", 15) == 0) {
                challenge_mode();
            } 
            else if (strncmp(mode_start, "view_scoreboard", 15) == 0) {
                char *mode_param = strstr(post_data, "score_mode=");
                if (mode_param) {
                    mode_param += 11; // skip "score_mode="
                    if (strncmp(mode_param, "practice", 8) == 0) {
                        display_practice_scores_html();
                    } else if (strncmp(mode_param, "normal", 6) == 0) {
                        display_normal_scores_html();
                    } else if (strncmp(mode_param, "challenge", 9) == 0) {
                        display_challenge_scores_html();
                    } else {
                        printf("<p>⚠️ Unknown scoreboard mode: %s</p>", mode_param);
                    }
                } else {
                    printf("<p>⚠️ No mode specified for scoreboard</p>");
                }
            } 
            else {
                printf("<p>⚠️ Unknown mode: %s</p>", mode_start);
            }

            printf("<br><a href='/index.html'>Back to Home</a>");
            printf("</body></html>");
            return 0;
        }
    }

    // HTML index page
    printf("<html><head><meta charset='UTF-8'><title>Typing Speed Tester</title></head><body>");
    if (strcmp(username, "Guest") == 0) {
        printf("<h1>Welcome to Typing Speed Tester</h1>");
        printf("<p>Choose a mode to start:</p>");
    } else {
        printf("<h1>Hello, %s!</h1>", username);
        printf("<p>Choose a mode to begin:</p>");
    }

    // Links to static HTML pages
    printf("<a href='/practice.html'>Practice Mode</a><br>");
    printf("<a href='/normal.html'>Normal Mode</a><br>");
    printf("<a href='/challenge.html'>Challenge Mode</a><br>");
    printf("<a href='/scoreboard.html'>Scoreboard</a><br>");

    printf("</body></html>");
    return 0;
}