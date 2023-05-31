#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "C:\Users\Aashish Nandakumar\Desktop\VSC Code files\C-Project\2_RSA\RSAmodified1.c"
// #include "C:\Users\Aashish Nandakumar\Desktop\VSC Code files\C-Project\2_Wallet\WalletMod.c"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREY "\033[1;30m"

#define ANSI_COLOR_RESET "\x1b[0m"

void displayTitlesFromDatabase()
{
    system("cls");
    printf(ANSI_COLOR_CYAN "Files stored in the cloud:\n" ANSI_COLOR_RED);
    FILE *file;
    char line[100];

    file = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/4_Cloud/Cloud_Database2.txt", "r");
    if (file == NULL)
    {
        printf(ANSI_COLOR_RED "Cloud database error\n" ANSI_COLOR_RESET);
        exit(1);
    }

    while (fgets(line, 100, file) != NULL)
    {

        printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET, line);
    }
    fclose(file);
}

static float bal = 450.6774543f;
int contract()
{
    system("cls");
    float amt, tran;
    int op;
    srand(time(NULL));

    amt = rand() % 5 + 0.00434f;
    tran = rand() % 3 + 0.0000078767f;

    printf(ANSI_COLOR_GREY "BALANCE: %f INR\n\n" ANSI_COLOR_RESET, bal);

    printf(ANSI_COLOR_GREY "FROM: admin\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREY "TO: BlockVault\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREY "AMOUNT: %f\n" ANSI_COLOR_RESET, amt);
    printf(ANSI_COLOR_GREY "TRANSACTION FEE: %f\n" ANSI_COLOR_RESET, tran);

    printf(ANSI_COLOR_GREY "\n1-Proceed and 2-Cancel" ANSI_COLOR_RESET);
    printf("\n--> ");
    scanf("%d", &op);
    if (op == 2)
        return 1;
    else
    {
        bal -= (amt + tran);
        return 0;
    }
}

static int index2 = 1;
int uploadDocuments()
{
    system("cls");
    int done = 0;
    int choice1, z = 1;
    displayTitlesFromDatabase();

    printf(ANSI_COLOR_CYAN "Do u want to browse files(1-YES/2-NO): \n" ANSI_COLOR_RESET);
    scanf("%d", &choice1);
    if (choice1 == 1)
    {
        DIR *folder, *folder2;
        struct dirent *files, *readAgain;

        folder = opendir("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/1_Client/toUpload");
        if (folder == NULL)
        {
            printf(ANSI_COLOR_RED "Unable to open files\n" ANSI_COLOR_RESET);
            exit(1);
        }

        while ((files = readdir(folder)) != NULL)
        {
            if (files->d_type == DT_REG)
            {
                printf(ANSI_COLOR_YELLOW "%d: %s\n" ANSI_COLOR_RESET, z, files->d_name);
                z++;
            }
        }

        int file_no, index = 1;
        char file_name[100];
        printf(ANSI_COLOR_CYAN "Enter the file you want to upload(choose the number against it): " ANSI_COLOR_RESET);
        scanf("%d", &file_no);

        folder2 = opendir("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/1_Client/toUpload");
        if (folder2 == NULL)
        {
            printf(ANSI_COLOR_RED "Unable to open files\n" ANSI_COLOR_RESET);
            exit(1);
        }

        while ((readAgain = readdir(folder2)) != NULL)
        {
            if (readAgain->d_type == DT_REG)
            {
                if (index == file_no)
                {
                    strcpy(file_name, readAgain->d_name);
                    break;
                }
                index++;
            }
        }
        closedir(folder);
        closedir(folder2);

        int n = contract();
        if (!n)
        {
            FILE *fp;
            fp = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/4_Cloud/Cloud_Database2.txt", "a");
            if (fp == NULL)
            {
                printf(ANSI_COLOR_RED "ERROR opening wallet databse\n" ANSI_COLOR_RESET);
                exit(1);
            }

            // fseek(fp, 0L, SEEK_END);
            fprintf(fp, "\n%d:%s", index2++, file_name);
            fclose(fp);

            char path[200];

            sprintf(path, "C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/1_Client/toUpload/%s", file_name);
            RSA_Algorithm_Initiate(path, file_no, 'E', file_name);
            printf(ANSI_COLOR_CYAN "\nFile successfully uploaded\n" ANSI_COLOR_RESET);
            done = 1;
        }
        else
        {
            printf(ANSI_COLOR_RED "Unable to browse files, action restricted!!\n" ANSI_COLOR_RESET);
        }

        int op;
        printf("press 1 for exit\n");
        printf("--> ");
        scanf("%d", &op);
        if (op)
            return done;
    }
    else
        return done;
}

int downloadDocuments()
{

    system("cls");
    int done = 0;
    int set = 0;
    displayTitlesFromDatabase();

    int file_no;
    printf(ANSI_COLOR_CYAN "Coose the file no. to download\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "-->" ANSI_COLOR_RESET);
    scanf("%d", &file_no);

    FILE *file;
    char file_name[100];

    file = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/4_Cloud/Cloud_Database2.txt", "r");
    if (file == NULL)
    {
        printf(ANSI_COLOR_RED "Cloud database error\n" ANSI_COLOR_RESET);
        exit(1);
    }

    char getLine[100];
    fseek(file, 0L, SEEK_SET);
    while (fgets(getLine, sizeof(getLine), file) != NULL)
    {
        int file_index;
        if (sscanf(getLine, "%d:%s", &file_index, file_name) == 2 || file_index != file_no)
        {
            set++;
            // printf(ANSI_COLOR_CYAN "Beginning download...\n" ANSI_COLOR_RESET);
        }
    }
    fclose(file);
    int n = contract(); //* Have to sign contract to move further

    if (!n)
    {

        // printf("\nFilename: %s, file no %d\n", file_name, file_no);
        if (!set)
        {
            printf(ANSI_COLOR_RED "File not found!!!!\n" ANSI_COLOR_RESET);

            // return done;
        }
        char path[200];
        sprintf(path, "C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/1_Client/toUpload/%s", file_name);

        RSA_Algorithm_Initiate(path, file_no, 'D', file_name);

        printf(ANSI_COLOR_CYAN "\nFile successfully downloaded\n" ANSI_COLOR_RESET);
        done = 1;
        int op;
        printf(ANSI_COLOR_CYAN "press 1 for exit\n" ANSI_COLOR_RESET);
        printf("--> ");
        scanf("%d", &op);
        if (op)
            return done;
    }
    else
        return done;
}

void knowMoreAboutUs()
{
    system("cls");
    int op;

    printf(ANSI_COLOR_YELLOW "BLOCKVAULT GOVERNMENT SERVICES\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\tDocumentVault is a secure document management platform that uses blockchain technology and cloud storage to store and transfer government documents securely. Our platform is designed to provide a tamper-proof and transparent system for storing, sharing, and tracking sensitive documents.\n" ANSI_COLOR_RESET);

    printf("\n" ANSI_COLOR_YELLOW "FEATURES\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t1. Secure storage: All documents are stored on a distributed blockchain network, ensuring that they cannot be tampered with or deleted without leaving a trace.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t2. Encrypted transmission: All documents are encrypted during transit to ensure that they remain secure and protected from unauthorized access.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t3. Access control: Our platform provides granular access controls, allowing users to specify who can access, view, and edit documents.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t4. Audit trail: All activity on the platform is logged and recorded, providing a complete audit trail of who accessed, viewed, and edited documents.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t5. Easy integration: Our platform can be easily integrated with existing systems, allowing government agencies to quickly and easily adopt our solution.\n" ANSI_COLOR_RESET);

    printf("\n" ANSI_COLOR_YELLOW "HOW IT WORKS\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\tOur platform uses a combination of blockchain technology and cloud storage to provide a secure and transparent document management solution. When a document is uploaded to the platform, it is encrypted and stored on the blockchain network. The document is then replicated across multiple nodes on the network, ensuring that it is always available and cannot be lost or deleted.\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\tWhen a user wants to access a document, they must first authenticate themselves using their credentials. Once authenticated, the user can access, view, and edit the document, based on their access level. All activity on the platform is logged and recorded, allowing administrators to monitor and track who accessed, viewed, and edited documents.\n" ANSI_COLOR_RESET);

    printf("\n" ANSI_COLOR_YELLOW "GETTING STARTED\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\tTo get started with DocumentVault, please contact us to schedule a demo of our platform. Our team will work with you to understand your document management needs and provide a customized solution that meets your requirements.\n" ANSI_COLOR_RESET);

    printf("\n" ANSI_COLOR_YELLOW "SUPPORT\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\tIf you have any questions or need assistance with our platform, please contact our support team at support@documentvault.com.\n" ANSI_COLOR_RESET);

    printf("\n" ANSI_COLOR_YELLOW "LICENSE\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\tDocumentVault is licensed under the MIT License. See LICENSE for more information.\n" ANSI_COLOR_RESET);

    printf(ANSI_COLOR_CYAN "press 1 for exit\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "--> " ANSI_COLOR_RESET);
    scanf("%d", &op);
    if (op)
        return;
}

void BlochainDatabaseUpdate(char data, int valid)
{
    FILE *file;
    file = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/3_Blockchain/BlockChainDatabase.txt", "a");

    if (data == 'U')
    {
        if (valid == 1)
            fprintf(file, "File succesfully uploaded to cloud database\n");
        else
            fprintf(file, "File failed to uploaded to cloud database\n");
    }

    else if (data == 'D')
    {
        if (valid == 1)
            fprintf(file, "File successfully downloaded from the cloud database\n");
        else
            fprintf(file, "File failed to downloaded from the cloud database\n");
    }
    fclose(file);
}

// static int ref3 = 0;
int menu()
{
    int choice;

    while (1)
    {
        system("cls");
        printf(ANSI_COLOR_CYAN "Welcome to BlockVault Government Services, please select one of the following choices: \n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_CYAN "\n1: Upload documents\n2: Download Documents\n3: Know more about us\n4: Exit the application\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_CYAN "--> " ANSI_COLOR_RESET);
        scanf("%d", &choice);
        int valid = 0;
        switch (choice)
        {
        case 1:

            valid = uploadDocuments();
            BlochainDatabaseUpdate('U', valid);
            return 0;
        case 2:

            valid = downloadDocuments();
            BlochainDatabaseUpdate('D', valid);
            return 0;
        case 3:
            knowMoreAboutUs();
            return 0;
        case 4:
            return 1;
        default:
            printf(ANSI_COLOR_CYAN "Mistakes do happen, looks like you have selected an option which doesn't exist, please try again\n" ANSI_COLOR_RESET);
        }
    }
}

// static int ref2 = 0;
int cloud(void)
{
    int val;

    val = menu();
    return val;
}