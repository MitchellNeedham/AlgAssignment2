/* * * * * * *
 * Directed Acyclic Graph module for Assignment 1
 *
 * created for COMP20007 Design of Algorithms 2020
 * written by Mitchell Needham <mneedham@student.unimelb.edu.au>
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dag.h"
#include "util.h"


//create node for dag and return pointer to it
Dag *create_node(int ID) {

    //allocate memory to dag and to child array of pointers
    Dag *new_node = malloc(sizeof(Dag));
    *new_node->child = malloc(sizeof(Dag));

    //initialise node
    new_node->ID = ID;
    new_node->parents = 0;
    *new_node->child = NULL;
    new_node->children = 0;
    
    return new_node;
}


//reference node as child to parent node
void add_child(Dag *node, Dag *child) {
    
    node->child[node->children] = child;

    //keep count parents and children
    node->children++;
    child->parents++;
}

void print_node(Dag *node) {


}


//runs algorithm designed to determine whether an acyclic path
//to all nodes can be completed
//
//this algorithm works by starting at the root (0) and cycling
//through all children until a child with only one parent is found
//
//the child with one parent is the next node in the path and this
//node is therefore passed back into the function recursively
//
//the algorithm fails (path not possible) when two children have one
//parent or when the position of a node with no children is not equal
//to the total number of nodes
int complete_path(Dag *node, int pos, int total) {
    Dag *child = NULL;
    int i = 0;

    //run through children of the node
    for (i = 0; i < node->children; i++) {

        //check if one parent
        if (node->child[i]->parents == 1) {
            
            //assign child node to 'child'
            //if 'child' already assigned, return false
            if (child == NULL) {
                child = node->child[i];
            } else {
                return 0;
            }
        
        //if child has more parents, do not select this node
        //and remove from parent count
        } else {
            node->child[i]->parents--;
        }
    }

    //if child node assigned, repeat process with new node
    if (child != NULL) {

        if (complete_path(child, pos + 1, total) == 1) {
            return 1;
        }
    }

    //if pos of end of path is equal to total node
    //then the path completed succesfully
    if (pos == total) {
        return 1;
    }

    return 0;
}

/*void free_dag_node(Dag *node) {
    free(node);
}*/




