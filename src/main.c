// Designed to show a simple menu to choose between modes
#include <stdio.h>
#include "modes.h"

int main() {
    int choice;

    do
    {
        printf("\nTyping Speed Tester\n");
        printf("1. Practice Mode\n");
        printf("2. Normal Mode\n");
        printf("3. Challenge Mode\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        
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
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }while(choice!=4);
    return(0);
}