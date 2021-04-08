#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef struct list_t list_t;
typedef struct list_node_t list_node_t;

struct list_t
{
  list_node_t * root;
  list_node_t * last;
  int size;
};

struct list_node_t
{
  list_node_t * next;
  list_node_t * previous;
  void *        object;
};

list_t* new_list();
list_node_t* new_list_node();
void add_node(list_t* list, void * object);
void* pop_back_of_list(list_t* list);


#endif
