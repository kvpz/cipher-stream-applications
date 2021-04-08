#include <stdio.h>
#include "player.h"
#include "linkedlist.h"

void
get_card_from_deck(player_t* player, deck_t* deck)
{
  card_t * card = deck_pop(deck);
  add_node(player->hand, card);
  player->hand_total_value += card->value;
}

player_t*
initialize_new_player(int id)
{
  player_t * player = malloc(sizeof(player_t));
  player->id = id;
  player->hand = new_list();
  player->hand_total_value = 0;
  player->winner = false;
  
  return player;
}

void print_player_cards(player_t* player)
{
  list_node_t * node = player->hand->root;
  card_t *      first_five_cards[5] = {{NULL}};
  card_t *      next_five_cards[5] = {{NULL}};
  card_t *      last_three_cards[3] = {{NULL}};
  
  for(int i = 0; i < 13; ++i)
  {
    if (5 > i)
    {
      first_five_cards[i%5] = (card_t*)node->object;
    }
    else if ((4 < i) && (10 > i))
    {
      next_five_cards[i%5] = (card_t*)node->object;
    }
    else
    {
      last_three_cards[i%10] = (card_t*)node->object;
    }
    
    node = node->next;	    
  }

  printf("\n"
	 "******************************************************************\n");
  if (0 == player->id) /* Dealer (Player 0) */
  {
    printf("**              PLAYER #%d (DEALER) HAND OF CARDS                **\n", player->id);
  }
  else
  {
    printf("**                  PLAYER #%d HAND OF CARDS                     **\n", player->id);
  }
  printf("******************************************************************\n"
	 "*                                                                *\n"
	 "*                                                                *\n",
	 player->id);

  print_row_of_five_cards(first_five_cards);
  print_row_of_five_cards(next_five_cards);
  print_row_of_three_cards(last_three_cards);
  
  printf("*                                                                *\n");
  if (99  < player->hand_total_value)
  {
    printf("*                           SCORE: %d                           *\n", player->hand_total_value);
  }
  else
  {
    printf("*                         SCORE: %d                              *\n", player->hand_total_value);
  }
  printf("*                                                                *\n"
	 "******************************************************************\n");
}

void print_cards_eight_player_game(player_t* player)
{
  list_node_t * node = player->hand->root;

  card_t * first_three_cards[3] = {{NULL}};
  card_t * last_three_cards[3] = {{NULL}};
  
  for(int i = 0; i < 6; ++i)
  {
    if (3 > i)
    {
      first_three_cards[i] = (card_t*)node->object;
    }
    else
    {
      last_three_cards[i%3] = (card_t*)node->object;
    }
    node = node->next;	          
  }

  printf("\n"
	 "******************************************************************\n");
  if (0 == player->id) /* Dealer */
  {
    printf("**              PLAYER #%d (DEALER) HAND OF CARDS                **\n", player->id);
  }
  else
  {
    printf("**                  PLAYER #%d HAND OF CARDS                     **\n", player->id);
  }
  printf("******************************************************************\n"
	 "*                                                                *\n"
	 "*                                                                *\n",
	 player->id);

  print_row_of_three_cards(first_three_cards);
  print_row_of_three_cards(last_three_cards);
  
  printf("*                                                                *\n");
  if (99  < player->hand_total_value)
  {
    printf("*                           SCORE: %d                           *\n", player->hand_total_value);
  }
  else
  {
    printf("*                         SCORE: %d                              *\n", player->hand_total_value);
  }
  printf("*                                                                *\n"
	 "******************************************************************\n");
}
