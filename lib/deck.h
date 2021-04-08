#ifndef HEADER_DECK
#define HEADER_DECK
#include <stdbool.h>
#include "utility.h"
#include "card.h"

#define DECK_SIZE 52

typedef struct deck_t deck_t;

// static deck_t*
deck_t *  deck_initialize_empty_deck(void);

deck_t * deck_initialize_with_cards(void);
card_t * deck_pop(deck_t*);
void     deck_push(deck_t*, card_t*);
bool     deck_is_empty(deck_t*);
bool     deck_is_full(deck_t*);

void deck_print_card_values(deck_t*);

struct deck_t
{
  int        stack_top;
  card_t *   cards[DECK_SIZE];
};



#endif
