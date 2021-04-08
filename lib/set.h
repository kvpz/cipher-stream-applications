/*
  This file defines an interface for a balanced binary search tree, or (height-balanced) AVL tree.
  The file is called set because the implementation essentially defines
  and ordered set.
  
  The tree data structure created has been optimized in the sense that it has
  been manually balanced.  The key value of the root vertex has been hard-coded
  to be the value 8 because it is already known that the key values that will
  be inserted into the tree are evenly dispersed from 2 to 17.
 */
#ifndef SET_H
#define SET_H
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "linkedlist.h"

typedef struct tree_node_t tree_node_t;

/* Structures */
typedef struct
{
  tree_node_t * root_node;

} tree_t;

struct tree_node_t
{
  tree_node_t * left_child;
  tree_node_t * right_child;
  list_t *      list_of_objects;
  int key;
};

/* function prototypes */
tree_t *      new_tree();
tree_node_t * new_node();
tree_node_t * get_node(tree_t* tree, int value);

void tree_insert(tree_t* tree, void* object, int value);

#endif
