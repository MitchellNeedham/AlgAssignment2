/* * * * * * *
 * Text Analysis module for Assignment 2.
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by <Insert Name Here>
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "text_analysis.h"
#include "trie.h"
#include "queue.h"
#include "linkedlist.h"

#define MAX_LENGTH 100
#define MAX_RESULTS 5

// Build a character level trie for a given set of words.
//
// The input to your program is an integer N followed by N lines containing
// words of length < 100 characters, containing only lowercase letters.
//
// Your program should built a character level trie where each node indicates
// a single character. Branches should be ordered in alphabetic order.
//
// Your program must output the pre-order traversal of the characters in
// the trie, on a single line.
void problem_2_a() {
  // initialise trie
  struct TrieNode *root = getNode();
  
  // initialise variables
  char *string = (char*) malloc((MAX_LENGTH + 1) * sizeof(char*));
  int length = 0;
  scanf("%d", &length);

  // get strings and insert into trie
  while (scanf("%s[^/n]", string) == 1) {
    insert(root, string);
  }

  // print trie
  printf("^\n");
  printTrie(root);

  freeTrie(root);
}

// Using the trie constructed in Part (a) this program should output all
// prefixes of length K, in alphabetic order along with their frequencies
// with their frequencies. The input will be:
//   n k
//   str_0
//   ...
//   str_(n-1)
// The output format should be as follows:
//   an 3
//   az 1
//   ba 12
//   ...
//   ye 1
void problem_2_b() {

  // initialise trie
  struct TrieNode *root = getNode();

  // initialise variables
  char *str = (char*) malloc((MAX_LENGTH + 1) * sizeof(char*));
  int str_length = 0;
  int prefix_len = 0;
  int top_level = 0; // top level of trie
  scanf("%d %d", &str_length, &prefix_len);

  // insert strings into trie
  while (scanf("%s[^/n]", str) == 1) {
    insert(root, str);
  }

  // create empty prefix string
  char *prefix_str = (char*) malloc((prefix_len + 1) * sizeof(char));
  prefix_str[prefix_len] = '\0';

  // create linkedlist node
  struct LLNode *node = initLinkedList(prefix_len);
  struct LLNode *head = node;

  // searches prefixes of length = prefix_len and adds them to a linked list
  searchPrefixes(root, node, prefix_len, top_level, prefix_str);

  // prints frequency of each prefix
  while (node->next != NULL) {
    printf("%s %d\n", node->string, getFrequency(root, node->string));
    node = node->next;
  }

  freeLinkedList(head);
  freeTrie(root);

}

// Again using the trie data structure you implemented for Part (a) you will
// provide a list (up to 5) of the most probable word completions for a given
// word stub.
//
// For example if the word stub is "al" your program may output:
//   0.50 algorithm
//   0.25 algebra
//   0.13 alright
//   0.06 albert
//   0.03 albania
//
// The probabilities should be formatted to exactly 2 decimal places and
// should be computed according to the following formula, for a word W with the
// prefix S:
//   Pr(word = W | stub = S) = Freq(word = W) / Freq(stub = S)
//
// The input to your program will be the following:
//   n
//   stub
//   str_0
//   ...
//   str_(n-1)
// That is, there are n + 1 strings in total, with the first being the word
// stub.
//
// If there are two strings with the same probability ties should be broken
// alphabetically (with "a" coming before "aa").
void problem_2_c() {
  // initialise variables
  int string_count = 0;
  char *stub = (char*) malloc((MAX_LENGTH + 1) * sizeof(char*));
  char *string = (char*) malloc((MAX_LENGTH + 1) * sizeof(char*));
  
  scanf("%d", &string_count);
  scanf("%s[^/n]", stub);

  int prefix_len = strlen(stub);
  

  // create linked list and assign head and node
  struct LLNode *node = initLinkedList(MAX_LENGTH + 1);
  struct LLNode *tail = node;

  // initiliase trie
  struct TrieNode *root = getNode();
   
  
  // get strings
  while (scanf("%s[^/n]", string) == 1) {
    
    // get substring
    char substring[prefix_len];
    memcpy(substring, string, prefix_len); // copy string from index 0 to prefix_len
    substring[prefix_len] = '\0'; // add null terminator

    // check if stub is a substring of the string
    if (strcmp(substring, stub) == 0) {

      // add to trie and linked list
      insert(root, string);
      tail = addFreqData(tail, string, getExactFrequency(root, string));
    }
  }
  
  
  // sort linked list according to frequency and alphanumeric value
  sortList(node);
  
  // assign tail to end of list
  tail = tail->prev;

  // get stub frequency
  double stub_freq = getFrequency(root, stub);

  // print data for first five strings
  int i = 0;
  while (i < MAX_RESULTS && tail != NULL) {
    printf("%.2f %s\n", (double)tail->data/stub_freq, tail->string);
    tail = tail->prev;
    i++;
  }

  freeTrie(root);
  freeLinkedList(node);
}
