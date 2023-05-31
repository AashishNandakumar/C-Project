#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
long long int suggested_e = 65537;

// function to check whether a number is prime number or not
int isPrime(long long int n)
{
    if (n <= 1)
        return 0;
    for (long long int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// function to generate a random prime number between given ranges
long long int generateRandomPrime(long long int min, long long int max)
{
    srand(time(NULL));
    long long int n;
    do
    {
        n = rand() % (max + 1) + min;
    } while (!isPrime(n));

    return n;
}

// Function used to calculate: (a*b)%c
long long int power(long long int a, long long int b, long long int c)
{
    /*  I made use of binary exponentiation algorithm, fast and
        effficient method of computing large powers of a number modulo another number.
    */

    long long int result = 1;

    a %= c; //* To make sure a is within the range of c to prevent overflow

    while (b > 0)
    {

        if (b % 2 == 1) //* checks the lSB of b
            result = (result * a) % c;

        b /= 2; //* moves to the next bit
        a = (a * a) % c;
    }

    return result;
}

long long int gcd(long long int a, long long int b)
{
    long long int temp;
    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long int choose_e(long long int phi_n)
{
    long long int e = 2;
    while (e < phi_n)
    {
        if (gcd(e, phi_n) == 1)
            return e;
        else
            e++;
    }
    return -1; // no suitable e found
}

// Function to generate public and private keys
void generateKeys(long long int p, long long int q, long long int *e, long long int *d, long long int *n)
{
    //* Step - 1  --> n = p*q
    *n = p * q;
    //* Step - 2  --> Phi(n) = (p-1)*(q-1)
    long long int phi = (p - 1) * (q - 1);
    //* Step - 3  --> calculate the encryption exponent(number bw 1 and (p-1)(q-1), relatively prime to (p-1)(q-1))
    *e = choose_e(phi);

    //* Step - 4  --> calculate the decryption exponent(inverse of e modulo (p-1)(q-1))
    *d = power(*e, -1, phi);
}

long long int encryptData(long long int data, long long int e, long long int n)
{
    /*
    --> To Encrypt a file using RSA we need to first convert it into bytes, Once it is in
        bytes, we can use the encryption exponent, e to encrypt the data using modular
        exponentiation.
    */
    long long int cipher_text;
    //* c = m^e mod n, (c = encrypted data, m = plaintext, n = modulus, e = encryption exponent)
    cipher_text = power(data, e, n);
    return cipher_text;
}

long long int decryptData(long long int data, long long int d, long long int n)
{
    /*
    --> To Decrypt the ciphertext, we can use the decryption exponent, d and modulus n
    */
    long long int plain_text;
    //* m = c^d mod n
    plain_text = power(data, d, n);
    return plain_text;
}

char *getFileContents(const char *file_name)
{
    /* OVERVIEW OF WHAT THIS FXN DOES
    --> It opens the file for reading in binary mode
    --> It seeks to the end of the file to determine its size
    --> It allocates a buffer to hold the contents of the file
    --> It reads the entire file into the buffer
    --> It closes the file
    --> It returns the buffer containing the file contents
    */

    FILE *fp;
    long fileSize;
    char *buffer;

    fp = fopen(file_name, "rb");

    //* If the file pointer is null, print the error message along with file name and exit
    if (!fp)
        perror(file_name), exit(1);

    //* seek to the end of file
    fseek(fp, 0L, SEEK_END);

    //* since we reached to the end of the file, ftell resturns the size of the file in bytes
    fileSize = ftell(fp);

    //* rewind the file pointer back to the beginning of the file
    rewind(fp);

    //* create a buffer to store file contents, +1 bcoz to include null terminator
    buffer = calloc(1, fileSize + 1);

    //* If the allocation fails, buffer will be null
    if (!buffer)
        fclose(fp), fputs("Memory allocation failed", stderr), exit(1);

    //* Read the data from the file and store them in the memory
    //* fread returns the no of items read, it should be 1 bcoz we are reading the entire file in one go
    if (fread(buffer, fileSize, 1, fp) != 1)
        fclose(fp), free(buffer), fputs("Entire Read failed", stderr), exit(1);

    fclose(fp);

    return buffer;
}

void writeFileContents(const char *file_name, char *buffer, int size)
{
    /*
    --> In this function you are writing to a file from what is stored in the buffer
    */

    FILE *fp;

    fp = fopen(file_name, "wb");
    if (!fp)
        perror(file_name), exit(1);

    //* Copy the contents of the buffer into the file
    if (fwrite(buffer, size, 1, fp) != 1)
        fclose(fp), fputs("Entire write Failed", stderr), exit(1);

    fclose(fp);
}

void RSA_Algorithm_Initiate(const char *OG_path_name, int file_no, int flag, const char *file_name)
{
    //* Load the contents of the file into the buffer
    char *file_contents = getFileContents(OG_path_name);
    int file_size = strlen(file_contents);

    //* Initiate a buffer to store encrypted data
    char encrypted_file_contents[file_size];
    //* Initiate a buffer to store decrypted data
    char decrypted_file_contents[file_size];

    if (flag == 'E')
    {
        //* it means u want to encrypt the file
        long long int p = generateRandomPrime(1000000000, 5000000000);
        long long int q = generateRandomPrime(1000000000, 5000000000);
        long long int e, d, n;
        generateKeys(p, q, &e, &d, &n);
        FILE *file1, *file2;
        file1 = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/2_Wallet/Wallet_keys.txt", "a");
        if (file1 == NULL)
        {
            printf("Wallet Database error\n");
            exit(1);
        }
        // fseek(file1, 0L, SEEK_END);
        fprintf(file1, "%s: %lld, %lld, %lld\n", file_name, e, d, n);

        fclose(file1);

        // store the credentials in the client files as well
        file2 = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/1_Client/Client_credentials/Note.txt", "a");
        if (file2 == NULL)
        {
            printf("Wallet Database error\n");
            exit(1);
        }
        // fseek(file2, 0L, SEEK_END);
        fprintf(file2, "\nFile Name : %s, public key: (%lld, %lld), private key: (%lld, %lld)", file_name, e, n, d, n);

        fclose(file2);

        //* Initiate a buffer to store encrypted data
        //* read one by one the data from OG buffer, encrypt them and store it in the encrypt buffer

        for (int i = 0; i < file_size; i++)
        {
            encrypted_file_contents[i] = encryptData(file_contents[i], e, n);
        }

        char pathToStore[200];
        sprintf(pathToStore, "C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/4_Cloud/Cloud_Database_Files/%s.enc", file_name);

        //* from the buffer u have to store it in an encrypted file
        writeFileContents(pathToStore, encrypted_file_contents, file_size);
    }
    else if (flag == 'D')
    {
        long long int e, d, n;

        FILE *fp;
        fp = fopen("C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/2_Wallet/Wallet_keys.txt", "r");
        if (fp == NULL)
        {
            printf("Wallet database connection error\n");
            exit(1);
        }
        char line[100];

        while (fgets(line, sizeof(line), fp) != NULL)
        {
            // printf("Hello1\n");
            char getFile[100];
            if (sscanf(line, "%s: %lld,%lld,%lld", getFile, &e, &d, &n) == 4 && strcmp(getFile, file_name) == 0)
            {
                printf("Downloading...\n");
            }
            // printf("File name2: %s", getFile);
        }
        // printf("Hello3");

        fclose(fp);
        //* read one by one the data from encrypt buffer, encrypt them and store it in the decrypt buffer

        for (int i = 0; i < file_size; i++)
        {
            // printf("hi");
            decrypted_file_contents[i] = decryptData(encrypted_file_contents[i], d, n);
            decrypted_file_contents[i] = file_contents[i];
        }

        //* from the buffer u have to store it in an decrypted file
        char path[100];
        // printf("%s", file_name);
        sprintf(path, "C:/Users/Aashish Nandakumar/Desktop/VSC Code files/C-Project/1_Client/toDownload/%s", file_name);
        writeFileContents(path, decrypted_file_contents, file_size);
    }
}
