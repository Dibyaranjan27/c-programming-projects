#ifndef BANKING_H
#define BANKING_H

#define FILENAME "accounts.txt"
#define TRANSACTION_FILE "transactions.txt"
#define USERS_FILE "users.txt"

// Colors for better UI
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

// Function Prototypes
void printHeader(char *title);
void registerUser();
int loginUser();
void createAccount();
void viewAccounts();
void depositMoney();
void withdrawMoney();
void transferMoney();
void viewTransactionHistory();
int updateBalance(int accountNo, float amount, int isDeposit);
void logTransaction(int accountNo, char *type, float amount, float balance);

#endif
