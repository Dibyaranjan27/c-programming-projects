#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "banking.h"

// Structure for Bank Accounts
typedef struct {
    int accountNo;
    char name[50];
    float balance;
} Account;

void registerUser() {
    FILE *file = fopen(USERS_FILE, "a");
    if (!file) {
        printf(RED "❌ Error opening users file!\n" RESET);
        return;
    }

    char username[50], password[50];

    printHeader("🆕 USER REGISTRATION");
    printf(YELLOW "Enter Username: " RESET);
    scanf("%s", username);
    printf(YELLOW "Enter Password: " RESET);
    scanf("%s", password);

    fprintf(file, "%s | %s\n", username, password);
    fclose(file);

    printf(GREEN "\n✅ Registration successful! You can now log in.\n\n" RESET);
}

int loginUser() {
    FILE *file = fopen(USERS_FILE, "r");
    if (!file) {
        printf(RED "❌ No users registered yet!\n" RESET);
        return 0;
    }

    char username[50], password[50], storedUsername[50], storedPassword[50];

    printHeader("🔐 USER LOGIN");
    printf(YELLOW "Enter Username: " RESET);
    scanf("%s", username);
    printf(YELLOW "Enter Password: " RESET);
    scanf("%s", password);

    while (fscanf(file, "%s | %s", storedUsername, storedPassword) != EOF) {
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            printf(GREEN "\n✅ Login Successful!\n\n" RESET);
            fclose(file);
            return 1;
        }
    }

    printf(RED "❌ Invalid username or password!\n\n" RESET);
    fclose(file);
    return 0;
}

// Function to create a new account
void createAccount() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf(RED "❌ Error opening accounts file!\n" RESET);
        return;
    }

    int accountNo;
    char name[50], password[50];
    float balance = 0.0;

    printf(YELLOW "Enter Account Number: " RESET);
    scanf("%d", &accountNo);
    printf(YELLOW "Enter Name: " RESET);
    scanf("%s", name);
    printf(YELLOW "Enter Password: " RESET);
    scanf("%s", password);

    fprintf(file, "%d | %s | %.2f | %s\n", accountNo, name, balance, password);
    fclose(file);

    printf(GREEN "✅ Account created successfully!\n\n" RESET);
}

// Function to view all accounts
void viewAccounts() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf(RED "❌ No accounts found!\n" RESET);
        return;
    }

    int accountNo;
    char name[50], password[50];
    float balance;

    printf(GREEN "\n📂 List of Accounts:\n" RESET);
    printf("------------------------------------------------\n");
    printf("Account No  |  Name  |  Balance ($)\n");
    printf("------------------------------------------------\n");

    while (fscanf(file, "%d | %s | %f | %s", &accountNo, name, &balance, password) != EOF) {
        printf("%-12d %-10s $%.2f\n", accountNo, name, balance);
    }

    printf("------------------------------------------------\n\n");
    fclose(file);
}

// Function to update balance
int updateBalance(int accountNo, float amount, int isDeposit) {
    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (!file || !tempFile) {
        printf(RED "❌ Error: Unable to open accounts file!\n" RESET);
        return 0;
    }

    int acc;
    char name[50], password[50];
    float balance;
    int found = 0;

    while (fscanf(file, "%d | %s | %f | %s", &acc, name, &balance, password) != EOF) {
        if (acc == accountNo) {
            found = 1;
            if (!isDeposit && balance < amount) {
                printf(RED "\n❌ Insufficient funds! Transaction failed.\n\n" RESET);
                fclose(file);
                fclose(tempFile);
                remove("temp.txt");
                return 0;
            }
            balance = isDeposit ? (balance + amount) : (balance - amount);
            printf(GREEN "\n✅ Transaction Successful! New Balance: $%.2f\n\n" RESET, balance);
        }
        fprintf(tempFile, "%d | %s | %.2f | %s\n", acc, name, balance, password);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf(RED "\n❌ Account not found!\n\n" RESET);
        remove("temp.txt");
        return 0;
    }

    remove(FILENAME);
    rename("temp.txt", FILENAME);
    return 1;
}

// Function to log transactions
void logTransaction(int accountNo, char *type, float amount, float balance) {
    FILE *file = fopen(TRANSACTION_FILE, "a");
    if (!file) {
        printf(RED "❌ Error opening transaction log!\n" RESET);
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(file, "%d | %d-%02d-%02d %02d:%02d:%02d | %s | %.2f | %.2f\n",
            accountNo, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec, type, amount, balance);

    fclose(file);
}

// Function to view transaction history
void viewTransactionHistory() {
    FILE *file = fopen(TRANSACTION_FILE, "r");
    if (!file) {
        printf(RED "❌ No transactions found!\n" RESET);
        return;
    }

    int accountNo;
    char dateTime[30], type[20];
    float amount, balance;

    printf(GREEN "\n📜 Transaction History:\n" RESET);
    printf("-----------------------------------------------------------------------------------\n");
    printf("Account No | Date & Time         | Type      | Amount ($) | Balance After ($)\n");
    printf("-----------------------------------------------------------------------------------\n");

    while (fscanf(file, "%d | %s | %s | %f | %f", &accountNo, dateTime, type, &amount, &balance) != EOF) {
        printf("%-11d %-18s %-10s $%.2f      $%.2f\n", accountNo, dateTime, type, amount, balance);
    }

    printf("-----------------------------------------------------------------------------------\n\n");
    fclose(file);
}

// Function to deposit money
void depositMoney() {
    int accNo;
    float amount;
    
    printf(YELLOW "\nEnter Account Number: " RESET);
    scanf("%d", &accNo);
    printf(YELLOW "Enter Amount to Deposit: " RESET);
    scanf("%f", &amount);

    if (updateBalance(accNo, amount, 1)) {
        printf(GREEN "\n✅ Successfully Deposited ₹%.2f into Account %d\n" RESET, amount, accNo);
        logTransaction(accNo, "Deposit", amount, 0);  // Log transaction
    } else {
        printf(RED "\n❌ Account not found! Deposit failed.\n" RESET);
    }
}

// Function to withdraw money
void withdrawMoney() {
    int accNo;
    float amount;

    printf(YELLOW "\nEnter Account Number: " RESET);
    scanf("%d", &accNo);
    printf(YELLOW "Enter Amount to Withdraw: " RESET);
    scanf("%f", &amount);

    if (updateBalance(accNo, -amount, 0)) {
        printf(GREEN "\n✅ Successfully Withdrawn ₹%.2f from Account %d\n" RESET, amount, accNo);
        logTransaction(accNo, "Withdrawal", amount, 0);  // Log transaction
    } else {
        printf(RED "\n❌ Insufficient balance or account not found.\n" RESET);
    }
}

// Function to transfer money between accounts
void transferMoney() {
    int senderAcc, receiverAcc;
    float amount;

    printf(YELLOW "\nEnter Sender Account Number: " RESET);
    scanf("%d", &senderAcc);
    printf(YELLOW "Enter Receiver Account Number: " RESET);
    scanf("%d", &receiverAcc);
    printf(YELLOW "Enter Amount to Transfer: " RESET);
    scanf("%f", &amount);

    if (updateBalance(senderAcc, -amount, 0) && updateBalance(receiverAcc, amount, 1)) {
        printf(GREEN "\n✅ Successfully Transferred ₹%.2f from Account %d to %d\n" RESET, amount, senderAcc, receiverAcc);
        logTransaction(senderAcc, "Transfer Out", amount, 0);
        logTransaction(receiverAcc, "Transfer In", amount, 0);
    } else {
        printf(RED "\n❌ Transfer failed! Check account details and balance.\n" RESET);
    }
}