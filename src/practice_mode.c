#include <stdio.h>
#include <string.h>
#include "file_handler.h"

#define MAX_LINES 100
#define MAX_LEN 256

void practice_mode() {
    int repeat;
    do {
        char saved_lines[MAX_LINES][MAX_LEN];
        int lines_read;
        int choice;
        //sos

        printf("\n--- Practice Mode ---\n");
        printf("1. Enter and save new practice text\n");
        printf("2. Start typing practice with saved text\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // clear input buffer

        if (choice == 1) {
            char input_text[1000];
            printf("\nEnter your new practice text (single paragraph):\n");
            fgets(input_text, sizeof(input_text), stdin);
            save_practice_data(input_text);
            printf("✅ Practice data saved!\n");
        } else if (choice == 2) {
            lines_read = load_data("practice_data.txt", saved_lines, MAX_LINES);
            if (lines_read <= 0) {
                printf("⚠️ No practice data found. Please add text first.\n");
                return;
            }
            //Remove trailing newlines from each loaded line
            for (int i = 0; i < lines_read; i++) {
                size_t len = strlen(saved_lines[i]);
                if (len > 0 && saved_lines[i][len - 1] == '\n') {
                    saved_lines[i][len - 1] = '\0';
                }
            }

            printf("\n📖 Begin typing the following lines:\n");

            int total_mistakes = 0;
            int total_chars = 0;

            for (int i = 0; i < lines_read; i++) {
                int len_expected=strlen(saved_lines[i]);

                printf("\nLine %d: %s\n", i + 1, saved_lines[i]);
                printf("Start Typing: ");

                // Remove trailing newline
                /*size_t len_input = strlen(input);
                if (len_input > 0 && input[len_input - 1] == '\n') {
                    input[len_input - 1] = '\0';
                    len_input--;
                }*/

                for(int j=0; j<len_expected; j++){
                    char expected_char=saved_lines[i][j];
                    char input_char;
                    input_char=getchar();

                    total_chars++;

                    if(input_char==expected_char){
                        putchar(input_char);
                        //continue;
                    } 
                    else{
                        total_mistakes++;
                        printf("\n❌ Incorrect input. Expected '%c' but got '%c'. Please try again for this character.\n", expected_char, input_char);

                        while(1){
                            input_char=getchar();
                            total_mistakes++; 
                            if(input_char==expected_char){
                                putchar(input_char);
                                break; 
                            } 
                            else {
                                printf("\n❌ Still incorrect. Expected '%c', got '%c'. Try again:\n", expected_char, input_char);
                            }
                        }
                    }
                    /*
                     // Consume trailing newline user inputs after each line
                      int c;
                      while ((c = getchar()) != '\n' && c != EOF) {
                      // Discard
                      }
                    */
                }
            }

            printf("\n🎯 Practice session complete.\n");
            printf("📝 Total characters typed: %d\n", total_chars);
            printf("❌ Total character mistakes made: %d\n", total_mistakes);
            float accuracy = 0.0f;
            if (total_chars > 0) {
                accuracy = ((float)(total_chars - total_mistakes) / total_chars) * 100.0f;
            }
            printf("🎯 Accuracy: %.2f%%\n", accuracy);
        } else {
            printf("Invalid choice. Try again.\n");
        }

        // Ask if user wants to retry practice
        printf("\nDo you want to practice again? (1 = Yes / 0 = No): ");
        scanf("%d", &repeat);
        while (getchar() != '\n'); // clear input buffer

    } while (repeat == 1);
} 