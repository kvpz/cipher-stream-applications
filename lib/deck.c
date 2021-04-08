#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

deck_t*
deck_initialize_empty_deck()
{
  deck_t* deck    = malloc(sizeof(deck_t));
  deck->stack_top = -1;
      
  return deck;
}

deck_t*
deck_initialize_with_cards()
{
  deck_t* deck = deck_initialize_empty_deck(); 
  
  for(Ranks rank = two; rank <= ace; ++rank)
  {
    for(Suits suit = clubs; suit <= spades; ++suit)
    {
      deck_push(deck, new_card(suit, rank));
    }
  }
    
  return deck;
}

card_t*
deck_pop(deck_t* deck)
{
  if (-1 == deck->stack_top)
  {
    return NULL;
  }
  
  return deck->cards[deck->stack_top--];
}
  
void
deck_push(deck_t* deck, card_t* card)
{
  if (!deck_is_full(deck))
  {
    deck->cards[++deck->stack_top] = card;
  }
}

bool
deck_is_full(deck_t* deck)
{
  if (DECK_SIZE == (deck->stack_top + 1))
  {
    return true;
  }

  return false;
}

bool
deck_is_empty(deck_t* deck)
{
  if (-1 == deck->stack_top)
  {
    return true;
  }
  
  return false;
}
