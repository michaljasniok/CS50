// Implements a dictionary's functionality
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 6700;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);

    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    // TODO: Improve this hash function
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = (hash * 31 + tolower(word[i])) % N;
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    while (fscanf(file, "%s", word) == 1)
    {
        unsigned int num = hash(word);
        // if does not have nexts
        if (table[num] == NULL)
        {
            node *n = malloc(sizeof(node));
            strcpy(n->word, word);
            n->next = NULL;
            table[num] = n;
        }
        // if it has nexts
        else
        {
            node *n = table[num];
            while (n->next != NULL)
            {
                n = n->next;
            }
            node *x = malloc(sizeof(node));
            strcpy(x->word, word);
            x->next = NULL;
            n->next = x;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int size = 0;
    for(int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            size++;
            if (table[i]->next != NULL)
            {
                node *n = table[i];
                while (n->next != NULL)
                {
                    n = n->next;
                    size++;
                }
            }
        }
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *temp = table[i]->next;
            free (table[i]);
            table[i] = temp;
        }
    }
    return true;
}
