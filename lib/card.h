#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  clubs = 1, diamonds, hearts, spades
} Suits;

typedef enum
{
  two = 1, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace
} Ranks;

typedef struct
{
  Suits suit;
  Ranks rank;
  int   value;
} card_t;

card_t* new_card(Suits suit, Ranks rank);

void print_top_edge_of_cards(int total_cards);
void print_row_three_or_five_of_cards(int, card_t**);
void print_fourth_row_of_cards(int, card_t**);
void print_row_two_of_cards(int, card_t**);
void print_row_six_of_cards(int, card_t**);
void print_bottom_edge_of_cards(int total_cards, card_t**);

void print_row_of_five_cards(card_t**);
void print_row_of_three_cards(card_t**);

char get_visual_rank(card_t* card);

#endif
