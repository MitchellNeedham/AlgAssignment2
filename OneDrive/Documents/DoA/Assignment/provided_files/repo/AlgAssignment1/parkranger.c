/* * * * * * *
 * Park Ranger module for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * template by Tobias Edwards <tobias.edwards@unimelb.edu.au>
 * implementation by Mitchell Needham <mneedham@student.unimelb.edu.au>
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "parkranger.h"
#include "util.h"
#include "dag.h"

// This function must read in a ski slope map and determine whether or not
// it is possible for the park ranger to trim all of the trees on the ski slope
// in a single run starting from the top of the mountain.
//
// The ski slope map is provided via stdin in the following format:
//
//   n m
//   from to
//   from to
//   ...
//   from to
//
// Here n denotes the number of trees that need trimming, which are labelled
// {1, ..., n}. The integer m denotes the number "reachable pairs" of trees.
// There are exactly m lines which follow, each containing a (from, to) pair
// which indicates that tree `to` is directly reachable from tree `from`.
// `from` and `to` are integers in the range {0, ..., n}, where {1, ..., n}
// denote the trees and 0 denotes the top of the mountain.
//
// For example the following input represents a ski slope with 3 trees and
// 4 reachable pairs of trees.
//
// In this example your program should return `true` as there is a way to trim
// all trees in a single run. This run is (0, 2, 1, 3).
//
// Your function should must:
//  - Read in this data from stdin
//  - Store this data in an appropriate data structure
//  - Run the algorithm you have designed to solve this problem
//  - Do any clean up required (e.g., free allocated memory)
//  - Return `true` or `false` (included in the stdbool.h library)
//
// For full marks your algorithm must run in O(n + m) time.



bool is_single_run_possible() {
  
  int init_vals[2] = { 0 };
  int node_vals[2] = { 0 };
  int i = 0;
  bool possible_path = false;
 
  //read initial values into array
  scanf("%d %d", &init_vals[0], &init_vals[1]);

  //create and initialise array of nodes with size provided by test file
  Dag *nodes[init_vals[0]];

  for (i = 0; i <= init_vals[0]; i++) {
    nodes[i] = create_node(i);
  }

  //read rest of data and connect child nodes to parent nodes
  while (scanf("%d %d", &node_vals[0], &node_vals[1]) == 2) {
    add_child(nodes[node_vals[0]], nodes[node_vals[1]]);
  }

  //run algorithm to determine if a single path with all nodes
  //is possible
  possible_path = complete_path(nodes[0], 0, init_vals[0]);

  //free nodes
  for (i = 0; i <= init_vals[0]; i++) {
    free_dag_node(nodes[i]);
  }
  
  return possible_path;
}







