// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// declare global int to store size
int dictsize = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    //declare pointer to store adress of current node
    node *ptr = root;

    // Buffer for a word
    char word[LENGTH + 1];

    for (int i = 0; i < LENGTH + 1; i++)
    {
        word[i] = 0;
    }

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {

        // make pointer to current place in trie structure and intitialise to root
        ptr = root;

        // make variable to store chaacter as int representing position in alphabet
        int alphaindex;

        // iterate over letters in word
        for (int i = 0; i < LENGTH; i++)
        {

            char alpha = word[i];

            // if word i == to ' character check ptr children and make new node if necesary
            if (alpha == 39)
            {
                alphaindex = 26;
                if (ptr-> children[alphaindex] == NULL)
                {
                    node *n = malloc(sizeof(node));

                    if (n == NULL)
                    {
                        return 1;
                    }

                    n->is_word = false;

                    for (int j = 0; j < N; j++)
                    {
                        n->children[j] = NULL;
                    }


                    // set 27th element of children to new node
                    ptr -> children[alphaindex] = n;
                }

                // set ptr to ptr[26]

                ptr = ptr -> children[alphaindex];

            }

            else
            {

                // adjust alphainex
                alphaindex = islower((int) alpha) ? (int) alpha - 97 : (int) alpha - 65;

                //check location for NULL and make new index if necessary
                if (ptr -> children[alphaindex] == NULL)
                {
                    node *n = malloc(sizeof(node));

                    if (n == NULL)
                    {
                        return 1;
                    }

                    n->is_word = false;

                    for (int k = 0; k < N; k++)
                    {
                        n->children[k] = NULL;
                    }

                    // set children[alphaindex] to new node
                    ptr -> children[alphaindex] = n;

                    //set ptr to new alphaindex element of array which its self points to the new node
                    ptr = ptr -> children[alphaindex];
                }

                else
                {

                    //set ptr to new alphaindex element of array which its self points to the new node
                    ptr = ptr -> children[alphaindex];

                }


            }



            // if the character is 0 word is over, set is_word and return to while loop
            if ((char) word[i + 1] == 0)
            {
                ptr -> is_word = true;

                break;
            }



        }



    }

    //printf("Size of dictionary = %i\n", size);

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

int sizer(node *ptr)
{
     for (int i = 0; i < 27; i++)
     {
        if (ptr -> children[i] != NULL)
        {
            sizer(ptr -> children[i]);
        }
    }

    if (ptr -> is_word)
    {
        dictsize ++;
    }

    return 0;

}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    node *ptr = root;

    sizer(ptr);

    return abs(dictsize);
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //declare pointer to store adress of current node
    node *ptr = root;

    //declare bool to return
    bool isword = false;

    // declare variable to store alpha index
    int alphaindex;

    for (int i = 0; i < LENGTH; i++)
    {

        char alpha = word[i];

        // if ' set to word[26]
        if (alpha == 39)
        {
            alphaindex = 26;
        }
        else
        {
            // adjust alphainex
            alphaindex = islower((int) alpha) ? (int) alpha - 97 : (int) alpha - 65;
        }


        if (alphaindex < 0 || alphaindex > 26)
        {
            isword = false;
            printf("Characters alpha index %i of word %s out of bounds\n", i, word);
            return 10;
            break;
        }

        //check element alphindex for null
        if (ptr -> children[alphaindex] == NULL)
        {
            isword = false;
            break;
        }

        ptr = ptr-> children[alphaindex];

        // check if end of word and if so if valid word
        if (i < LENGTH && word[i + 1] == '\0')
        {
            isword = ptr -> is_word;
            break;
            //return isword;

        }

    }

    return isword;
}

bool unloader(node *ptr)
{
    // make cursore pointer to move trough struct
    node *cursor;
    // make array to store pointers to instances of recursion to free once they are finished
    node *tofree[27];

    // initialise elemets of array to NULL for checking when freeing
    for (int k = 0; k <= 26; k++)
    {
        tofree[k] = NULL;
    }

    // itterate over pointers in children to check for NULL and call unloaded if necessary
    for (int i = 0; i <= 26; i++)
    {
        if (ptr -> children[i] != NULL)
        {
            cursor = ptr ->children[i];
            tofree[i] = cursor;
            unloader(cursor);
        }
    }

    // when the stack has collapsed back to this point itterate over node array and free
    for (int j = 0; j <= 26; j++)
    {
        if (tofree[j] != NULL)
        {
            free(tofree[j]);
        }
    }


    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *ptr;

    bool unloaded = false;

    ptr = root;

    unloaded = unloader(ptr);

    free(ptr);

    return unloaded;
}
