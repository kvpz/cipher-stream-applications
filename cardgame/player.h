#ifndef PLAYER_H
#define PLAYER_H
//#include <stdbool.h>

#include "linkedlist.h"
#include "deck.h"

typedef struct
{
  int       id;
  list_t *  hand;
  int       hand_total_value;
  bool      winner;
} player_t;

player_t* initialize_new_player(int);
void get_card_from_deck(player_t*, deck_t*);
void print_player_cards(player_t*);
void print_cards_eight_player_game(player_t*);

#endif
