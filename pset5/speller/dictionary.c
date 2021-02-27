// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "dictionary.h"
#include <ctype.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned  int N = 16384 ;
unsigned  int words_number = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    
    unsigned int hash_value = hash(word);
    node *traverse = table[hash_value] ;
    if(traverse == NULL) {
        return false ;
    }
    while(traverse != NULL) {
        if(strcasecmp(word , traverse->word) == 0) {
            return true;
        }
        traverse = traverse->next;
    }
    return false;
}

// Hashes word to a number
unsigned  int hash(const char *word)
{
    unsigned  int count;
    unsigned  int hashValue = 0;
    for(count = 0; word[count] != '\0'; count++){
        hashValue = word[count] + (hashValue << 6) + (hashValue << 16) - hashValue;
    }
    return (hashValue%N);

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file_ptr = fopen(dictionary , "r") ;
    if(file_ptr == NULL)  {
        return false ;
    }
    char *rWord = (char*)malloc(sizeof(char) * (LENGTH+1));
    if (rWord == NULL) {
        return false ;

    }
    while(fscanf(file_ptr , "%s" ,rWord) != EOF){

        node *temp = malloc(sizeof(node));
        if (temp == NULL ) {
            return false;
        }
        strcpy(temp->word , rWord);
        unsigned  int hash_index = hash(rWord);
        temp->next = table[hash_index];
        table[hash_index]= temp;
        words_number++;
    }

    fclose(file_ptr);
    file_ptr = NULL;
    free(rWord);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(words_number > 0)
       return words_number ;
    else
       return 0;

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (unsigned  int i = 0 ; i < N ; i++) {
        while(table[i] != NULL) {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}
