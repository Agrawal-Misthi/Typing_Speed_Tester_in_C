#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>


#include <string.h>
#include "modes.h"
#include "file_handler.h"

#define MAX_LINES 100
#define MAX_LEN 256

using namespace std;

void practice_mode() {
    int repeat;
    do {
        char saved_lines[MAX_LINES][MAX_LEN];
        int lines_read;
        int choice;

        cout << "\n--- Practice Mode ---\n";
        cout << "1. Enter and save new practice text\n";
        cout << "2. Start typing practice with saved text\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear leftover newline from input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            char input_text[1000];
            cout << "\nEnter your new practice text (single paragraph):\n";
            cin.getline(input_text, sizeof(input_text));

            save_practice_data(input_text);
            cout << "✅ Practice data saved!\n";
        }

        else if (choice == 2) {
            lines_read = load_data("practice_data.txt", saved_lines, MAX_LINES);
            if (lines_read <= 0) {
                cout << "⚠️ No practice data found. Please add text first.\n";
                return;
            }

            // Trim newline characters
            for (int i = 0; i < lines_read; i++) {
                size_t len = strlen(saved_lines[i]);
                if (len > 0 && saved_lines[i][len - 1] == '\n')
                    saved_lines[i][len - 1] = '\0';
            }

            cout << "\n📖 Begin typing the following lines:\n";

            int total_mistakes = 0;
            int total_chars = 0;

            for (int i = 0; i < lines_read; i++) {
                queue<char> q;
                for (size_t j = 0; j < strlen(saved_lines[i]); j++)
                    q.push(saved_lines[i][j]);

                cout << "\nLine " << i + 1 << ": " << saved_lines[i] << "\n";
                cout << "Start Typing: " << flush;

                while (!q.empty()) {
                    char expected = q.front();
                    char input_char = getch(); 

                    if (input_char == expected) {
                        putchar(input_char);
                        q.pop();
                        total_chars++;
                    } else if (input_char != '\n' && input_char != EOF) {
                        total_mistakes++;
                        cout << "\n❌ Expected '" << expected << "', got '"
                             << input_char << "'. Try again:\n";
                        while (true) {
                             input_char = getch(); 
                            if (input_char == expected) {
                                putchar(input_char);
                                q.pop();
                                total_chars++;
                                break;
                            } else if (input_char != '\n' && input_char != EOF) {
                                total_mistakes++;
                                cout << "\n❌ Expected '" << expected << "', got '"
                                     << input_char << "'. Try again:\n";
                            }
                        }
                    }
                }

                int cont_choice;
                cout << "\nNext line? (1 = Yes / 0 = Quit): ";
                cin >> cont_choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (cont_choice == 0) break;
            }

            cout << "\n🎯 Practice session complete.\n";
            cout << "📝 Total characters typed: " << total_chars << "\n";
            cout << "❌ Mistakes: " << total_mistakes << "\n";

            float accuracy = (total_chars > 0)
                                 ? ((float)(total_chars - total_mistakes) / total_chars) * 100.0f
                                 : 0.0f;
            cout << "🎯 Accuracy: " << accuracy << "%\n";
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }

        cout << "\nPractice again? (1 = Yes / 0 = No): ";
        cin >> repeat;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (repeat == 1);
}