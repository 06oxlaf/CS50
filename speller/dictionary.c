// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

int cnt = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 626;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
            cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if(word[1] != 0)
        return ((toupper(word[0]) - 'A')*25) + (toupper(word[1])- 'A');
    else
        return ((toupper(word[0]) - 'A')*25);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open dictiionary
     FILE *file = fopen(dictionary, "r");
    if(dictionary == NULL)
        return false;
    char word[LENGTH + 1];
    int i = 0;
    int n = 0;
    while (fscanf(file, "%s", word) != EOF)
    {
        node *p = malloc(sizeof(node));
        if (p != NULL)
            strcpy((p->word), word);
        if (table[hash(word)] == NULL)
            table[hash(word)] = p;
        else
        {
            p->next = table[hash(word)];
            table[hash(word)] = p;
        }
        cnt = cnt + 1;
    }
    fclose(file);

    //Read strings one file at a time
    // create a new node for each word
    // hash word to obtain a havelue
    //insert node into hash table
    // read dictionary- use has table, array of linked lists
    //
    // if succesful - true
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return cnt;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node* tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
    }
        return true;
    }


