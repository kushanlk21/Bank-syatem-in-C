#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 50

typedef struct {
    int accountNumber;
    char accountHolderName[50];
    float balance;
    int isActive;
} Account;

Account bankAccounts[MAX_ACCOUNTS];

void initializeAccounts() {
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        bankAccounts[i].accountNumber = i + 1;
        bankAccounts[i].isActive = 0;
    }
}

void loadAccountsFromFile() {
    FILE *file = fopen("bank_accounts.txt", "r");
    if (file != NULL) {
        fread(bankAccounts, sizeof(Account), MAX_ACCOUNTS, file);
        fclose(file);
    }
}

void saveAccountsToFile() {
    FILE *file = fopen("bank_accounts.txt", "w");
    if (file != NULL) {
        fwrite(bankAccounts, sizeof(Account), MAX_ACCOUNTS, file);
        fclose(file);
    }
}

void openAccount() {
    int availableAccounts = MAX_ACCOUNTS;
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (bankAccounts[i].isActive) {
            availableAccounts--;
        }
    }

    if (availableAccounts <= 0) {
        printf("No available accounts slots.\n");
        return;
    }

    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (!bankAccounts[i].isActive) {
            printf("Enter account holder name: ");
            scanf("%s", bankAccounts[i].accountHolderName);
            printf("Enter initial balance: ");
            scanf("%f", &bankAccounts[i].balance);
            bankAccounts[i].isActive = 1;
            printf("Account opened successfully\n");
            saveAccountsToFile();
            break;
        }
    }
}

void closeAccount() {
    int accountNumber;
    printf("Enter account number to close: ");
    scanf("%d", &accountNumber);

    int closed = 0;
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (bankAccounts[i].isActive && bankAccounts[i].accountNumber == accountNumber) {
            bankAccounts[i].isActive = 0;
            closed = 1;
            printf("Account closed successfully\n");
            saveAccountsToFile();
            break;
        }
    }

    if (!closed) {
        printf("Account not found or already closed\n");
    }
}

void updateAccount() {
    int accountNumber;
    printf("Enter account number to update: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (bankAccounts[i].isActive && bankAccounts[i].accountNumber == accountNumber) {
            printf("Enter new account holder name: ");
            scanf("%s", bankAccounts[i].accountHolderName);
            printf("Enter new balance: ");
            scanf("%f", &bankAccounts[i].balance);
            printf("Account updated successfully\n");
            saveAccountsToFile();
            return;
        }
    }
    printf("Account not found\n");
}

void displayAccounts() {
    printf("Bank Accounts:\n");
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (bankAccounts[i].isActive) {
            printf("Account Number: %d, Holder Name: %s, Balance: %.2f\n", bankAccounts[i].accountNumber, bankAccounts[i].accountHolderName, bankAccounts[i].balance);
        }
    }
}

void findAccount() {
    int accountNumber;
    printf("Enter account number to find: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (bankAccounts[i].isActive && bankAccounts[i].accountNumber == accountNumber) {
            printf("Account found:\n");
            printf("Account Number: %d, Holder Name: %s, Balance: %.2f\n", bankAccounts[i].accountNumber, bankAccounts[i].accountHolderName, bankAccounts[i].balance);
            return;
        }
    }
    printf("Account not found\n");
}

int main() {
    initializeAccounts();
    loadAccountsFromFile();

    int choice;
    do {
        printf("\nBank System Menu\n");
        printf("1. Open an account\n");
        printf("2. Close an account\n");
        printf("3. Update an account\n");
        printf("4. Find an account\n");
        printf("5. Display all accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                openAccount();
                break;
            case 2:
                closeAccount();
                break;
            case 3:
                updateAccount();
                break;
            case 4:
                findAccount();
                break;
            case 5:
                displayAccounts();
                break;
            case 6:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
