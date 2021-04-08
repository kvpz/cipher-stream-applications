#ifndef SHUFFLER_H
#define SHUFFLER_H
#include <stdlib.h>
#include "deck.h"
#include "set.h"
#include "linkedlist.h"
#include "ciphersuite.h"

typedef tree_t set_of_card_values;

void biased_fisher_yates_shuffle(deck_t*, crypto_deck_t*);
void free_shuffling_heap_memory(tree_t*);
int rand_card_value_generator(crypto_t*);

#endif
