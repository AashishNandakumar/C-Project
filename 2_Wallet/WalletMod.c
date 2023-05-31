#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:\Users\Aashish Nandakumar\Desktop\VSC Code files\C-Project\3_Blockchain\blockchain.c"
#define ANSI_COLOR_GREEN "\x1b[32m"

#define ANSI_COLOR_RESET "\x1b[0m"

void WalletSync();

void logIn(char username[20], char password[20])
{

    FILE *file;
    file = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/2_Wallet/Wallet_Database.txt", "r");
    if (file == NULL)
    {
        printf(ANSI_COLOR_GREEN "\nWallet Database down!!!\n" ANSI_COLOR_RESET);
        exit(0);
    }

    char line[100];
    char tokenPWD[100];
    char tokenUSR[100];
    int found = 0;

    //* Now begin scanning the databse
    while (fgets(line, sizeof(line), file) != NULL)
    {
        //* sscanf() --> used to read formatted input from a string
        //* The return type is the number of successful matches made during the scanning process
        if (sscanf(line, "%[^-]-%s", tokenUSR, tokenPWD) == 2)
        {

            if (strcmp(tokenPWD, password) == 0 && strcmp(tokenUSR, username) == 0)
            {
                found = 1;
                break;
            }
        }
    }

    FILE *fp;
    if (found)
    {

        int op22;
        printf(ANSI_COLOR_GREEN "\nLog-In successfull\n" ANSI_COLOR_RESET);

        printf(ANSI_COLOR_GREEN "\nType (1) to continue\n" ANSI_COLOR_RESET);
        printf("--> ");
        scanf("%d", &op22);

        printf("%d", op22);
        if (op22 == 1)
        {
            WalletSync();
        }
        else
        {

            exit(1);
        }

        return;
    }
    else
    {
        int choice;
        printf(ANSI_COLOR_GREEN "\nNo records found for the given credentials\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Do u want to create a new accout?, select a choice:  \n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "1: Create a new account\n2: Exit application\n" ANSI_COLOR_RESET);
        printf("--> ");
        scanf("%d", &choice);
        if (choice == 2)
            exit(0);

        fp = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/2_Wallet/Wallet_Database.txt", "a");

        if (fp == NULL)
        {
            printf(ANSI_COLOR_GREEN "\nWallet Database down\n");
            return;
        }

        fprintf(fp, "%s-%s\n", username, password);
        fclose(fp);
        printf(ANSI_COLOR_GREEN "\nUsername and password successfully added to database\n" ANSI_COLOR_RESET);

        int op;
        printf(ANSI_COLOR_GREEN "\nType (1) to continue\n" ANSI_COLOR_RESET);
        printf("--> ");
        scanf("%d", &op);
        if (op)
            WalletSync();
        else
            exit(1);
    }
    fclose(fp);
    fclose(file);
    return;
}

void WalletSync()
{
    Initiate();
}

void start()
{
    char username[20], password[20];
    system("cls");
    printf(ANSI_COLOR_GREEN "Welcome to Phanthom wallet, please provide the following credentials: \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "Provide Username: " ANSI_COLOR_RESET);
    printf("--> ");
    scanf("%s", username);
    printf(ANSI_COLOR_GREEN "Provide password: " ANSI_COLOR_RESET);
    printf("--> ");
    scanf("%s", password);

    logIn(username, password);

    system("cls");
    printf(ANSI_COLOR_GREEN "Thank you for choosing us as a service, we hope to see you again\n\n" ANSI_COLOR_RESET);
    return;
}
