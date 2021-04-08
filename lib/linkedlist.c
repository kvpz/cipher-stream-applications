#include "linkedlist.h"

list_t*
new_list()
{
  list_t * l = malloc(sizeof(list_t));
  l->root = NULL;
  l->last = NULL;
  l->size = 0;
  
  return l;
}

list_node_t*
new_list_node()
{
  list_node_t * node = malloc(sizeof(list_node_t));

  node->next     = NULL;
  node->previous = NULL;
  node->object   = NULL;
  
  return node;
}

void
add_node(list_t* list, void * object)
{
  if(NULL == list->root) /* case when list is empty */
  {
    list->root         = new_list_node();
    list->last         = list->root;
    list->root->object = object;
    list->size         = 1;
  }
  else /* find last node then attach a new node to it */
  {
    list_node_t * current_node = list->root; 
    
    while(NULL != current_node->next)
    {
      current_node = current_node->next;
    }
    
    current_node->next           = new_list_node();
    current_node->next->object   = object;
    current_node->next->previous = current_node;
    list->last                   = current_node->next;
    
    ++list->size;
  }
}

void*
pop_back_of_list(list_t* list)
{
  if(0 == list->size && NULL == list->root) /* case when list is empty */
  {
    return NULL;
  }
  
  void * list_node_object = list->last->object; /* store object before unlinking list node */

  if(NULL == list->last->previous) /* case when list only has one node */
  {
    free(list->root);
  }
  else
  {
    list->last = list->last->previous;
    free(list->last->next);
    list->last->next = NULL;
  }
  
  --list->size;
  
  return list_node_object;
}
