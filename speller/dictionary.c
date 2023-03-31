// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

int totalwords = 0;
bool loaded;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
     // TODO
    int hashed = hash(word); //hashes given word
    if (table[hashed] == NULL)
    {
        return false;
    }

    if (strcasecmp(table[hashed]->word, word) == 0) //compares it to a word in TABLE
    {
        return true;
    }
    else //if not in TABLE then follow linked list chain and check accordingly
    {
        for (node *tmp = table[hashed]->next; tmp != NULL; tmp = tmp->next)
        {
            if (strcasecmp(tmp->word, word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int sum = 0;
    int hash;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == '\'')
        {
            sum += toupper(word[i]);
        }
        else
        {
            sum += toupper(word[i]) - 'A';
        }
    }
        hash = sum % N;
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
         table[i] = NULL;
    }

    char buffer, lastletter;
    char holdword[LENGTH + 1];

    int letters = 0; //for storing words
    node *tmp; //outside of while loop

    //reading file until reaches end
    while (fread(&buffer, sizeof(char), 1, file) == sizeof(char))
    {
        //when it is a new line character
        if (buffer == 10)
        {
            totalwords++;
            holdword[letters] = '\0'; //nul value for end of word
            letters = 0;

            //create hash value for dictionary words
            int hashed = hash(holdword);

            //table[i] were already initiailzed to NULL
            if (table[hashed] == NULL)
            {
                //Create new node and save word to node
                tmp = malloc(sizeof(node));
                int l = 0;
                for(int i = 0; holdword[i] != '\0'; i++)
                {
                    tmp->word[i] = holdword[i];
                    l++;
                }
                tmp->word[l] = '\0';
                tmp->next = NULL;
                table[hashed] = tmp; //transfer first word of hash value to table
            }
            else //create new nodes when table[hash] is used
            {
                node *w = malloc(sizeof(node));
                if (w == NULL)
                {
                    return false;
                }

                w->next = table[hashed];
                table[hashed] = w;
                int l = 0;
                for(int i = 0; holdword[i] != '\0'; i++)
                {
                    w->word[i] = holdword[i];
                    l++;
                }
                w->word[l] = '\0';
            }
        }
        else //for storings words before newline char
        {
            holdword[letters] = buffer;
            letters++;
        }
    }

    fclose(file);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO just makes use of global variable
    if (loaded)
    {
        return totalwords;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO - might need nested for loop to clear from the end first
    if (loaded)
    {
        for (int i = 0; i < N; i++)
        {
            while (table[i] != NULL)
            {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
            }
        }

        return true;
    }
    return false;
}
