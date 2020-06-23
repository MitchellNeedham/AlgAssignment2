/* * * * * * *
 * Deque module (i.e., double ended queue) for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Mitchell Needham <mneedham@student.unimelb.edu.au>
 */

// You must not change any of the code already provided in this file, such as
// type definitions, constants or functions.
//
// You may, however, add additional functions and/or types which you may need
// while implementing your algorithms and data structures.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"
#include "util.h"

int save_deque_size = 0;

// Create a new empty Deque and return a pointer to it
Deque *new_deque() {
	Deque *deque = malloc(sizeof(*deque));
	assert(deque);

	deque->top = NULL;
	deque->bottom = NULL;
	deque->size = 0;

	return deque;
}

// Free the memory associated with a Deque
void free_deque(Deque *deque) {
  // Remove (and thus free) all of the nodes in the Deque.
  while (deque->size > 0) {
    deque_remove(deque);
  }

	// Free the deque struct itself
	free(deque);
}

// Create a new Node with a given piece of data
Node *new_node(Data data) {
  Node *node = malloc(sizeof(*node));
  assert(node);

  node->next = NULL;
  node->prev = NULL;
  node->data = data;

  return node;
}

// Free the memory associated with a Node
void free_node(Node *node) {
  free(node);
}

// Add an element to the top of a Deque
void deque_push(Deque *deque, Data data) {
  Node *new = new_node(data);

  if (deque->size > 0) {
    new->next = deque->top;
    deque->top->prev = new;
  } else {
    // If the Deque was initially empty then new is both the top and bottom
    deque->bottom = new;
  }

  deque->top = new;
  deque->size++;
}

// Add an element to the bottom of a Deque
void deque_insert(Deque *deque, Data data) {
  Node *new = new_node(data);

  if (deque->size > 0) {
    new->prev = deque->bottom;
    deque->bottom->next = new;
  } else {
    // If the Deque was initially empty then new is both the top and bottom
    deque->top = new;
  }

  deque->bottom = new;
  deque->size++;
}

// Remove and return the top element from a Deque
Data deque_pop(Deque *deque) {
  if (deque->size == 0) {
    exit_with_error("can't pop from empty Deque");
  }

  Data data = deque->top->data;
  Node *old_top = deque->top;

  if (deque->size == 1) {
    deque->top = NULL;
    deque->bottom = NULL;
  } else {
    deque->top = old_top->next;
    deque->top->prev = NULL;
  }

  deque->size--;

  free(old_top);

  return data;
}

// Remove and return the bottom element from a Deque
Data deque_remove(Deque *deque) {
  if (deque->size == 0) {
    exit_with_error("can't remove from empty Deque");
  }

  Data data = deque->bottom->data;
  Node *old_bottom = deque->bottom;

  if (deque->size == 1) {
    deque->top = NULL;
    deque->bottom = NULL;
  } else {
    deque->bottom = old_bottom->prev;
    deque->bottom->next = NULL;
  }

  deque->size--;

  free(old_bottom);

  return data;
}

// Return the number of elements in a Deque
int deque_size(Deque *deque) {
  return deque->size;
}

// Print the Deque on its own line with the following format:
//   [x_1, x_2, ..., x_n]
//     ^              ^
//    top           bottom
void print_deque(Deque *deque) {
  Node *current = deque->top;
  int i = 0;

  printf("[");

  while (current) {
    printf("%d", current->data);
    // Print a comma unless we just printed the final element
    if (i < deque->size - 1) {
      printf(", ");
    }
    current = current->next;
    i++;
  }

  printf("]\n");
}

// Reverses the Deque using an iterative approach
void iterative_reverse(Deque *deque) {

  //create a temporary deque
  Deque *temp_deque = new_deque();

  //move data to temporary deque
  while (deque->size) {
    deque_push(temp_deque, deque_pop(deque));
  }
  
  //move data back to original deque with reversed order
  while (temp_deque->size) {
    deque_insert(deque, deque_pop(temp_deque));
  }

  //free temp deque
  free_deque(temp_deque);
}

// Reverses the Deque using a recursive approach
void recursive_reverse(Deque *deque) {

  //save deque size and print data
  if (save_deque_size == 0) {
    save_deque_size = deque->size;
  }

  //break recursion when deque is empty
  if (deque->size == 0) {
    return;
  }

  //remove data from deque
  Data data = deque_remove(deque);

  recursive_reverse(deque);

  //add data back to deque after it is empty in reversed order
  deque_push(deque, data);
}


// Splits the Deque given a critical value k, such that the Deque contains
// all elements greater than equal to k above (i.e., closer to the top)
// the elements less than k.
//
// Within the two parts of the array (>= k and < k) the elements remain
// in their original order.
//
// This function runs in linear time.
void split_deque(Deque *deque, int k) {
 
  //create individual deque for greater and lesser values than k
  Deque *lesser_values = new_deque();
  Deque *greater_values = new_deque();

  int data = 0;

  //run through main deque and move data to respective new deques
  while (deque_size(deque)) {
    data = deque_remove(deque);
    if (data >= k) {
      deque_push(greater_values, data);
    }
    else {
      deque_push(lesser_values, data);
    }
  }

  //move greater values back to main deque and free the deque
  //maintain original order of values
  while (deque_size(greater_values)) {
    deque_insert(deque, deque_pop(greater_values));
  }
  free_deque(greater_values);

  //move lesser values back to main deque and free the deque
  //while maintaining original order of values
  while (deque_size(lesser_values)) {
    deque_insert(deque, deque_pop(lesser_values));
  }
  free_deque(lesser_values);
}
