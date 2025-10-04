// Designed to show a simple menu to choose between modes
#include <stdio.h>
#include "modes.h"
#include "scoreboard.h"

int main() {
    int choice;

    do
    {
        printf("\nTyping Speed Tester\n");
        printf("1. Practice Mode\n");
        printf("2. Normal Mode\n");
        printf("3. Challenge Mode\n");
        printf("4. View Scoreboards\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
         
        scanf("%d", &choice);
        while (getchar() != '\n'); // clear input buffer

        switch (choice) {
            case 1:
                practice_mode();
                break;
            case 2:
                normal_mode();
                break;
            case 3:
                challenge_mode();
                break;
            case 4: {
                int mode_choice;
                printf("\nSelect scoreboard to view:\n");
                printf("1. Practice Mode\n");
                printf("2. Normal Mode\n");
                printf("3. Challenge Mode\n");
                printf("Enter your choice: ");
                scanf("%d", &mode_choice);
                while (getchar() != '\n'); // clear input buffer

                switch (mode_choice) {
                    case 1:
                        display_practice_scores();
                        break;
                    case 2:
                        display_normal_scores();
                        break;
                    case 3:
                        display_challenge_scores();
                        break;
                    default:
                        printf("⚠️ Invalid choice.\n");
                        break;
                }
                break;
            }
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("⚠️ Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}