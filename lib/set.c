#include "set.h"

static bool
compare(int a, int b)
{
  if(a > b)
  {
    return true;
  }

  return false;
}

tree_t*
new_tree()
{
  tree_t * tree        = malloc(sizeof(tree_t));
  tree->root_node      = new_node();
  tree->root_node->key = 8;

  return tree;
}

tree_node_t*
new_node()
{
  tree_node_t * node    = malloc(sizeof(tree_node_t));
  node->key             = 0;
  node->left_child      = NULL;
  node->right_child     = NULL;
  node->list_of_objects = new_list();

  return node;
}

tree_node_t*
get_node(tree_t* tree, int value)
{
  tree_node_t * tree_crawler = tree->root_node;
  tree_node_t * parent       = NULL;
  
  while(NULL != tree_crawler)
  {
    if (compare(value, tree_crawler->key))
    {
      parent       = tree_crawler;
      tree_crawler = tree_crawler->left_child;
    }
    else if (compare(tree_crawler->key, value))
    {
      parent       = tree_crawler;
      tree_crawler = tree_crawler->right_child;
    }
    else 
    {
      return tree_crawler;
    }
  }

  return parent; /* node with value does not exist. Return last node encountered. */
}

void
tree_insert(tree_t* tree, void* object, int value)
{
  tree_node_t * node = get_node(tree, value);
  
  if (compare(value, node->key))
  {
    node->left_child      = new_node();
    node->left_child->key = value;
    add_node(node->left_child->list_of_objects, object);
  }
  else if (compare(node->key, value))
  {
    node->right_child      = new_node();
    node->right_child->key = value;
    add_node(node->right_child->list_of_objects, object);
  }
  else
  {
    add_node(node->list_of_objects, object);
  }
}
