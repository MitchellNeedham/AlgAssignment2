#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

#include "queue.h"
#include "linkedlist.h"
#include "hashtable.h"


#define MAX_LENGTH 256
#define CHAR_BYTES 6

/* * * * * * *
 * Hashing module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Mitchell Needham
 */

#include "hash.h"
#include "hashtable.h"

// Implements a solution to Problem 1 (a), which reads in from stdin:
//   N M
//   str_1
//   str_2
//   ...
//   str_N
// And outputs (to stdout) the hash values of the N strings 1 per line.
void problem_1_a() {
  int mod = 0;
  int total_strings = 0;

  // allocate memory for string to be hashed
  char *string = (char*) malloc(MAX_LENGTH * sizeof(char*));

  // get initial values 
  scanf("%d %d", &total_strings, &mod);

  // hash each string and print result
  while (scanf("%s[^/n]", string) == 1) {
    printf("%d\n", hash(string, mod));
  }
}

// Implements a solution to Problem 1 (b), which reads in from stdin:
//   N M K
//   str_1
//   str_2
//   ...
//   str_N
// Each string is inputed (in the given order) into a hash table with size
// M. The collision resolution strategy must be linear probing with step
// size K. If an element cannot be inserted then the table size should be
// doubled and all elements should be re-hashed (in index order) before
// the element is re-inserted.
//
// This function must output the state of the hash table after all insertions
// are performed, in the following format
//   0: str_k
//   1:
//   2: str_l
//   3: str_p
//   4:
//   ...
//   (M-2): str_q
//   (M-1):
void problem_1_b() 
{
  int total_strings = 0;
  int mod = 0;
  int step = 0;

  // allocate memory for string to be hashed
  char *string = (char*) malloc(MAX_LENGTH * sizeof(char*));

  // initialise values
  scanf("%d %d %d", &total_strings, &mod, &step);
  char string_arr[total_strings][MAX_LENGTH];
  int count = 0;

  // create new hashtable
  struct Hashtable* hashtable = createHashtable(mod);

  // read strings and store them in array
  while (scanf("%s[^/n]", string) == 1) {
    strcpy(string_arr[count], string);
    count++;
  }

  int i = 0;
  while (i < total_strings) {
    // get hash value
    int hash_value = hash(string_arr[i], mod);

    // insert into hashtable and store the position it was inserted at
    int hash_pos = addToHashtable(hashtable, string_arr[i], hash_value, step);

    // if string could not be inserted, double mod and create new hashtable
    // and re-insert all strings 
    if (hash_pos == INT_MIN) {
      i = 0;
      mod *= 2;
      hashtable = createHashtable(mod);
      continue;
    }

    // if there are at least 2 elements in string_arr
    // sort string_arr in ascending hash value in hashtable
    if (i > 0) {
      for (int k = 0; k < i; k++) {

        // if new hash position is less than hash value of string in array
        // insert into hashed words in order of hash value
        if (getHashPosition(hashtable, string_arr[k]) > 
            getHashPosition(hashtable, string_arr[i])) {
          // create temporary empty string
          char temp[MAX_LENGTH];

          // copy new string to temp
          strcpy(temp, string_arr[i]);

          // move all strings between i and k forward one index
          for (int j = i; j >= k; j--) {
            strcpy(string_arr[j], string_arr[j-1]);
          }

          // copy temp (new string) into sorted position in array 
          strcpy(string_arr[k], temp);
          break;
        }
      }
    }
    i++;
  }

  // print hashtable
  printHashtable(hashtable);

  freeHashtable(hashtable);
}

// returns int value of alphanumeric character
int chr(char c) 
{
  if (c >= 'a' && c <= 'z') {
    return c - 'a';
  } else if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 26;
  } else if (c >= '0' && c <= '9') {
    return c - '0' + 52;
  }
  return -1;
}

// returns hash value of an alphanumeric string
int hash(char* string, int mod) {
  // create Queue to insert binary values into
  // size = max length * bytes of character (6)
  struct Queue* values = createQueue(MAX_LENGTH * CHAR_BYTES);

  int counter = 0;
  // while there is a character in string, enqueue binary values of each char
  while (string[counter] != '\0') {
    int char_val = chr(string[counter]);
    int power = 0;

    for (power = CHAR_BYTES - 1; power >= 0 ; power--) {
      // using & operator, determine if 2^n is used in binary representation of char
      if ((char_val & (int) pow(2, power)) == 0) {
        enqueue(values, 0);
      } else {
        enqueue(values, 1);
      }
    }
    counter++;
  }
  
  int total = 0;

  // while queue is not empty, implement horner's rule to get hash value
  while (!isEmpty(values)) {
    int coeff = dequeue(values);
    total = (total * 2 + coeff) % mod;
  }
  return total;
}


