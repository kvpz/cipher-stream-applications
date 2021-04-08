#include "shuffler.h"

void biased_fisher_yates_shuffle(deck_t* deck, crypto_deck_t* crypto)
{
  tree_t * card_tree = new_tree();
  
  /* transfer cards from deck to a card value ordered multimodal set */
  do
  {
    card_t * card = deck_pop(deck);
    tree_insert(card_tree, card, card->value);
  } while (!deck_is_empty(deck));

  /* Shuffle cards */  
  crypto->encrypt(card_tree, crypto, deck);

  free_shuffling_heap_memory(card_tree);
}

void
free_shuffling_heap_memory(tree_t* tree)
{
  const int minimum_card_value = 2;
  const int maximum_card_value = 17;
  for(int value = minimum_card_value; value < (maximum_card_value + 1); ++value)
  {
    tree_node_t * tree_crawler           = tree->root_node;
    tree_node_t * parent                 = NULL;
    bool        tree_crawler_went_left = false;
  
    while(NULL != tree_crawler)
    {
      if (value > tree_crawler->key)
      {
	parent                 = tree_crawler;
	tree_crawler           = tree_crawler->left_child;
	tree_crawler_went_left = true;
      }
      else if (tree_crawler->key > value)
      {
	parent                 = tree_crawler;
	tree_crawler           = tree_crawler->right_child;
	tree_crawler_went_left = false;
      }
      else 
      {
	/* 1. Free list object inside tree node */
	free(tree_crawler->list_of_objects);

	/* 2. Free the tree node if it is not the root */
	if (tree_crawler->key != 8)
	  free(tree_crawler);
	break;
      }
    }   
  }
  
  /* 2. Free tree root */
  //free(tree->root_node->list_of_objects);
  free(tree->root_node);
  
  /* 3. Free tree */
  free(tree);
}
