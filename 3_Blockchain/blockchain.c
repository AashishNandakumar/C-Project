#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\Aashish Nandakumar\Desktop\VSC Code files\C-Project\4_Cloud\CloudModifed1.c"
#include <time.h>

void Initiate();
//* Implementation of doubley linked list
struct block
{
    struct block *prevHash;

    int (*callCloud)(void); //* datatype varies --> Here this is used to establish connection with cloud
    int flag;               //* --> set the flag to 1 when it is created and used so it wont be modified again

    struct block *nextHash;

} *Head = NULL, *Tail = NULL;

static int count = 0;
//* Implementation of insert rear
void createNewBlock()
{

    if (Head == NULL)
    {
        Head = (struct block *)malloc(sizeof(struct block));
        Head->prevHash = NULL;
        Head->nextHash = NULL;
        Tail = Head;
        return;
    }

    struct block *newBlock, *ptr;
    newBlock = (struct block *)malloc(sizeof(struct block));

    ptr = Head;
    while (ptr->nextHash != NULL)
        ptr = ptr->nextHash;

    ptr->nextHash = newBlock;
    newBlock->prevHash = ptr;
    newBlock->nextHash = NULL;
    Tail = newBlock;
    return;
}

// static int ref1 = 0;

int handshakeCloud()
{

    FILE *fp;
    fp = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/3_Blockchain/BlockChainDatabase.txt", "a");
    if (fp == NULL)
    {
        printf("Blockchain database error\n");
        exit(1);
    }
    time_t currentTime;
    struct tm *localTime;

    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    //* We need to store the information abt whatever is happening on the blockchain into a database
    fprintf(fp, "\nActivity details: \n");
    fprintf(fp, "Time: %02d:%02d:%02d\n", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
    fprintf(fp, "Previous hash: %p\n", &Tail->prevHash);
    fprintf(fp, "Next hash: %p\n", &Tail->nextHash);
    fclose(fp);
    int val1;

    Tail->flag = 1;
    Tail->callCloud = cloud;
    val1 = Tail->callCloud();

    return val1;
}

void Initiate()
{

    //* For every transactions create a new block in the blockchain
    createNewBlock();

    //* Each block will initiate connection with the cloud
    int val2 = handshakeCloud();
    while (!val2)
    {
        createNewBlock();
        val2 = handshakeCloud();
    }
    return;
}

/*int Initiate()
{

    //* For every transactions create a new block in the blockchain
    createNewBlock();

    //* Each block will initiate connection with the cloud
    int val2 = handshakeCloud();

    return val2;
}
*/