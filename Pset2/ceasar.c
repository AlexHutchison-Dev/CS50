#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>

//Declare function
int encript(int a, int b);

////declare variables in main scope



int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage ./caesar key\n");
        return 0;
    }
    else
    {
        //iterate over characteris in argv1 and verify is number
        for (int i = 0; i < strlen(argv[1]); i++)
        {

            if (isdigit(argv[1][i]) != 0)
            {
                i++;
            }
            else
            {
                printf("Usage ./caesar key\n");
                return 0;
            }
        }


    }

    //Convert argument to int for key

    int key = atoi(argv[1]);

    string plainText = get_string("plaintext:  ");

    printf("ciphertext: ");

    // itterate over characters in plain text phrase
    for (int i = 0, j = strlen(plainText); i < j; i++)
    {

        if (isupper(plainText[i]) + islower(plainText[i]) == 0)
        {
            //if non letter character print un encripted
            printf("%c", plainText[i]);
            continue;
        }

        else
        {

        encript((int)plainText[i], key);

        }
    }

    printf("\n");

}

int encript(int a, int b)
    {
        // make int to store cipher text char
        char ci = a;
        int tmp = 0;
        int debug = isupper(a);
        if(isupper(a)> 0)
        {
            a -= 65;
            tmp = 65;
        }
        else
        {
            a -= 97;
            tmp = 97;

        }

            ci = ((a + b) % 26) + tmp;
            printf("%c", ci);
            return 0;
    }


