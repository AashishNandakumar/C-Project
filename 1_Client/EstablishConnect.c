#include <stdio.h>
#include "C:\Users\Aashish Nandakumar\Desktop\VSC Code files\C-Project\2_Wallet\WalletMod.c"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"

void eraseContents(char op)
{
    FILE *f1, *f3, *f4, *f5;
    f1 = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/1_Client/Client_credentials/Note.txt", "w");
    f3 = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/2_Wallet/Wallet_keys.txt", "w");
    f4 = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/3_Blockchain/BlockChainDatabase.txt", "w");
    f5 = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/4_Cloud/Cloud_Database2.txt", "w");
    fclose(f1);
    fclose(f3);
    fclose(f4);
    fclose(f5);

    if (op == 'y')
    {
        FILE *f2;
        f2 = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/2_Wallet/Wallet_Database.txt", "w");
        fclose(f2);
    }

    return;
}

int main()
{
    system("cls");
    char op;
    //* Begin the process of establishing connection with the wallet8
    printf(ANSI_COLOR_MAGENTA "Hey glad you are back, wanna start?(y/n)\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "--> " ANSI_COLOR_RESET);
    scanf("%c", &op);
    if (op == 'y')
        start();

    printf(ANSI_COLOR_MAGENTA "Hope you had a good day,\n" ANSI_COLOR_RESET);
    char op1, op2;
    printf(ANSI_COLOR_MAGENTA "Before leaving, Do you want to erase history?(y/n)\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "--> " ANSI_COLOR_RESET);
    scanf(" %c", &op1);
    printf(ANSI_COLOR_MAGENTA "Do you want to delete passwords too?(y/n)\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "--> " ANSI_COLOR_RESET);
    scanf(" %c", &op2);
    if (op1 == 'y')
    {
        eraseContents(op2);
        printf(ANSI_COLOR_MAGENTA "History successfully erased\n" ANSI_COLOR_RESET);
    }

    return 0;
}