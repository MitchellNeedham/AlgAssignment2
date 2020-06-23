// C implementation of search and insert operations 
// on Trie 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 


#include "trie.h"
#include "linkedlist.h"
  
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0]) 
#define ALPHABET_SIZE (26) 
#define CHAR_TO_INDEX(ch) ((int)ch - (int)'a') // converts char to index
#define INDEX_TO_CHAR(i) ((char)(i + 'a')) // converts index to char
#define END_OF_WORD_SYMBOL "$"

  
struct TrieNode 
{ 
    struct TrieNode *children[ALPHABET_SIZE]; 
    int frequency;
    bool isLast; 
}; 
  
// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode() 
{ 
    // create node
    struct TrieNode *node = (struct TrieNode*)malloc(sizeof(struct TrieNode)); 

    // initialise struct
    node->isLast = false; 
    node->frequency = 0;

    // initialise all children to null
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL; 
    }

    return node; 
} 
  
// inserts key into trie
void insert(struct TrieNode *root, char *key) 
{ 
    int level = 0; 
    int length = strlen(key); 
    int index = 0; 
  
    // create traverser to run through trie
    struct TrieNode *trav = root; 
  
    // checks if next char (child node) exists
    // if it doesn't: create it
    // if it does: add to frequency
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
        if (!trav->children[index]) {
            trav->children[index] = getNode();
        }
  
        trav = trav->children[index]; 
        trav->frequency++;
    } 
  
    // last node is leaf
    trav->isLast = true; 
} 
  
// prints trie
void printTrie(struct TrieNode *node) 
{ 
    // if end of word, print end symbol
    if (node->isLast || node == NULL) {
        printf("%s\n", END_OF_WORD_SYMBOL);
    }

    // run through children and if a child exists, print it
    // then continue recursive print
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            printf("%c\n", INDEX_TO_CHAR(i));
            printTrie(node->children[i]);
        }
    }
} 

// gets frequency of particular node or char (i.e how many strings it occurs in)
int getFrequency(struct TrieNode *node, char *key) {
    int length = strlen(key);

    // gets to node at end of key
    for (int i = 0; i < length; i++) {
        int index = CHAR_TO_INDEX(key[i]);
        node = node->children[index];
    }

    return node->frequency;
}

// gets exact frequency of string (i.e how many occurances of this exact string exist)
int getExactFrequency(struct TrieNode *node, char *key) {
    int length = strlen(key);

    // get to last node in key
    for (int i = 0; i < length; i++) {
        int index = CHAR_TO_INDEX(key[i]);
        node = node->children[index];
    }

    // get frequency
    int freq = node->frequency;

    // subtract frequencies of continuing nodes (longer strings)
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            freq -= node->children[i]->frequency;
        }
    }

    return freq;
}

// searches for strings within trie of an exact length
struct LLNode *searchPrefixes(struct TrieNode *t_node, struct LLNode *l_node, int length, int level, char *prefix) {

    // goes through children and adds it to prefix until required length reached
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (t_node->children[i] && level < length) {

            // add char to prefix string
            prefix[level] = INDEX_TO_CHAR(i);

            // increase level for continuation of prefix
            level++;
            l_node = searchPrefixes(t_node->children[i], l_node, length, level, prefix);
            
            // decrease level again for any new continuation of this prefix
            level--;
        }
    }

    // when prefix has reached required length, add it to the list
    if (level == length){
        return addString(l_node, prefix);
    }

    return l_node;
}

void freeTrie(struct TrieNode *node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            free(node->children[i]);
        } 
    }
    free(node);
}



  