
#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>

#include "linkedlist.h"

#define MAX_LEN 256

// initialises doubly linked list and returns start node
struct LLNode* initLinkedList(int length) 
{ 
    // allocate memory
    struct LLNode* node = (struct LLNode*)malloc(sizeof(struct LLNode)); 
    node->next = NULL;
    node->prev = NULL;
    node->string = (char*)malloc(length * sizeof(char));
    node->length = length;
    node->data = 0;
    return node; 
}

// creates new node and returns it
struct LLNode* newNode(struct LLNode *prev) {
    // allocate memory
    struct LLNode* node = (struct LLNode*)malloc(sizeof(struct LLNode)); 
    node->next = NULL;
    node->prev = prev;
    node->string = (char*)malloc(prev->length * sizeof(char));
    node->length = prev->length;
    node->data = 0;
    return node; 
}

// adds new node with string value (data set to 0 as it not required)
struct LLNode* addString(struct LLNode* node, char *s) {
    strcpy(node->string, s);
    return node->next = newNode(node);
}

// specialised function that adds node to linked list with string and frequency
// compares string value with previous nodes to ensure there are no duplicates
struct LLNode* addFreqData(struct LLNode* node, char *s, int data) {
    // create traverser node
    struct LLNode *trav = node;

    // iterate through list
    while (trav != NULL) {

        // if string already exists, update frequency for this string
        if (strcmp(s, trav->string) == 0) {
            trav->data = data;
            return node;
        }
        trav = trav->prev;
    }

    // if string does not already exist, add it and return new node
    strcpy(node->string, s);
    node->data = data;

    // return next node
    return node->next = newNode(node);
}

// sorts list
struct LLNode* sortList(struct LLNode* node) {
    struct LLNode *head = node;

    // iterate through list until second last node
    while(head->next->next != NULL) {

        // compare data values and swap if out of order
        // or if data values are the same, compare strings and swap if not
        // in alphabetic order
        if (head->next->data < head->data ||
         (head->next->data == head->data && 
         strcmp(head->next->string, head->string) >= 0)) {

            // create a temporary string to store one value for the swap
            char temp_str[strlen(head->string) + 1];

            // swap string values
            strcpy(temp_str, head->string);
            strcpy(head->string, head->next->string);
            strcpy(head->next->string, temp_str);

            // swap data values
            int temp_freq = head->data;
            head->data = head->next->data;
            head->next->data = temp_freq;

            head = node;
        } else {
            head = head->next;
        }
    }

    return NULL;
}

void freeLinkedList(struct LLNode* node) {
    free(node->string);
    if (node->next != NULL) {
        freeLinkedList(node->next);
    }
    free(node);    
}