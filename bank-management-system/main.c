#include <stdio.h>
#include "banking.h"

void printHeader(char *title) {
    printf("\n");
    printf("=====================================\n");
    printf("         %s\n", title);
    printf("=====================================\n");
}

int main() {
    int choice;
    int loggedIn = 0;

    while (1) {
        if (!loggedIn) {
            printHeader("🏦 BANKING SYSTEM LOGIN");
            printf(YELLOW "1. Register\n" RESET);
            printf(YELLOW "2. Login\n" RESET);
            printf(YELLOW "3. Exit\n" RESET);
            printf("=====================================\n");
            printf(YELLOW "Enter your choice: " RESET);
            scanf("%d", &choice);

            switch (choice) {
                case 1: registerUser(); break;
                case 2: loggedIn = loginUser(); break;
                case 3: printf(GREEN "\n👋 Exiting program. Thank you!\n" RESET); return 0;
                default: printf(RED "\n❌ Invalid choice! Try again.\n\n" RESET);
            }
        } else {
            printHeader("🏦 MAIN MENU");
            printf(YELLOW "1. Create Account\n" RESET);
            printf(YELLOW "2. View Accounts\n" RESET);
            printf(YELLOW "3. Deposit Money\n" RESET);
            printf(YELLOW "4. Withdraw Money\n" RESET);
            printf(YELLOW "5. Transfer Money\n" RESET);
            printf(YELLOW "6. View Transaction History\n" RESET);
            printf(YELLOW "7. Logout\n" RESET);
            printf("=====================================\n");
            printf(YELLOW "Enter your choice: " RESET);
            scanf("%d", &choice);

            switch (choice) {
                case 1: createAccount(); break;
                case 2: viewAccounts(); break;
                case 3: depositMoney(); break;
                case 4: withdrawMoney(); break;
                case 5: transferMoney(); break;
                case 6: viewTransactionHistory(); break;
                case 7: printf(GREEN "\n👋 Logged out successfully.\n" RESET); loggedIn = 0; break;
                default: printf(RED "\n❌ Invalid choice! Try again.\n\n" RESET);
            }
        }
    }

    return 0;
}
