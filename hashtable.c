
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <string.h>
#include <ctype.h>

#include "hashtable.h"

#define MAX_STRING_LENGTH 256

struct Hashtable
{ 
    int pos, capacity; 
    char** array; 
}; 

// This function creates a hashtable allowing for a number of string
// up to a specified capacity, then initialised variables 
struct Hashtable* createHashtable(int capacity) 
{ 
    // create struct and allocate memory
    struct Hashtable* hashtable = (struct Hashtable*) malloc(sizeof(struct Hashtable)); 
    
    // init variables
    hashtable->capacity = capacity; 
    hashtable->pos = 0; 

    // allocate memory for each string
    hashtable->array = malloc(hashtable->capacity * sizeof(char*)); 
    for (int i = 0; i < capacity; i++) {
        hashtable->array[i] = (char*) malloc((MAX_STRING_LENGTH + 1) * sizeof(char));
        strcpy(hashtable->array[i], "\0");
    }
    return hashtable; 
} 

// This function adds new hashed string to table, moving it forward by a
// specified increment should there be a collision
int addToHashtable(struct Hashtable* hashtable, char* string, int hashPos, int step) {
    int increment = step;
    
    // if position is already empty, put new string in and return value
    if (hashtable->array[hashPos][0] == '\0') {
            strcpy(hashtable->array[hashPos], string);
            return hashPos;
        }

    // if position is not empty, check all steps incrementally
    // until there is either an empty position or it cycles back to the
    // original position
    while (((hashPos + increment) % hashtable->capacity) != hashPos) {
        // get new position by adding step and using mod to cycle table
        int newPos = ((hashPos + increment) % hashtable->capacity);
        
        // if there is an empty position, insert string
        if (hashtable->array[newPos][0] == '\0') {
            strcpy(hashtable->array[newPos], string);
            return hashPos;
        }
        increment += step;
    }
    
    // return error value if string could not be inserted
    return INT_MIN;
}

// This function returns the value of the string position in the hash table
int getHashPosition(struct Hashtable* hashtable, char *string) {
    for (int i = 0; i < hashtable->capacity; i++) {
        if (strcmp(hashtable->array[i], string) == 0) {
            return i;
        }
    }
    return INT_MIN;
}

// prints hashtable
void printHashtable(struct Hashtable* hashtable) {
    int i = 0;
    for (i = 0; i < hashtable->capacity; i++) {
        printf("%d: %s\n", i, hashtable->array[i]);
        
    }
}

// frees memory from hashtable
void freeHashtable(struct Hashtable* hashtable) {
    for (int i = 0; i < hashtable->capacity; i++) {
        free(hashtable->array[i]);
    }
    free(hashtable->array);
    free(hashtable);
}
