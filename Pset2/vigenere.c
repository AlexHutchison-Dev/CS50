#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>

//Declare function
int encript(int a, int b, int c);
int alphabetNum(int * a);


////declare variables in main scope
int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage ./vigenere key\n");
        return 0;
    }
    else
    {
        //iterate over characteris in argv1 and verify is alpha
        for (int i = 0; i < strlen(argv[1]); i++)
        {

            if (isalpha(argv[1][i]) != 0)
            {
                i++;
            }
            else
            {
                printf("Usage ./vigenere key\n");
                return 0;
            }
        }


    }

    string plainText = get_string("plaintext:  ");

    printf("ciphertext: ");

    // itterate over characters in plain text phrase
    for (int i = 0, j = 0,k = strlen(plainText); i < k; i++)
    {

        //Declare variables to store current plain char, key char and offset beteen plain char and its alphabet number
        int plainchar = ((int) plainText[i]);
        int keychar = argv[1][j];
        int offset = plainchar;
        int cipherchar = 0;


        int keylen = strlen(argv[1]);

        if (isupper(plainchar) + islower(plainchar) == 0)
        {
            //if non letter character print un encripted
            printf("%c", plainchar);
            continue;
        }

        //Check j doesnot exceed character in key word
        if(j == keylen -1)
        {

            j = -1;
        }





        //Call functions to check plaintext is alpha and convert both plain text and key to int
        //referencing place in alabet
        alphabetNum(&plainchar);
        alphabetNum(&keychar);

        //set offset to difference in plainchar before and after alphNum
        offset -= plainchar;

        encript(plainchar, keychar, offset);
        j++;
    }

    printf("\n");
}

int alphabetNum(int * a)
{
    if (isupper(*a) > 0)
    {
        *a-=65;
    }
    else if (islower(*a) > 0)
    {
           *a -= 97;
    }

    return 0;
}

int encript(int a, int b, int c)
{
    int cipherchar = ((a + b) % 26) + c;
    printf("%c", cipherchar);
    return 0;
}



