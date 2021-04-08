#include "card.h"

card_t*
new_card(Suits suit, Ranks rank)
{
  card_t * card = malloc(sizeof(card_t)); 
  card->suit = suit;
  card->rank = rank;
  card->value = suit + rank;
  
  return card;
}

char
get_visual_rank(card_t* card)
{
  if (10 == card->rank) return 'J';
  if (11 == card->rank) return 'Q';
  if (12 == card->rank) return 'K';
  if (13 == card->rank) return 'A';
  
  return card->rank + 1U;
}

void print_top_edge_of_cards(int total_cards)
{
  printf("   ********** ");

  for(int i = 0; i < (total_cards - 2); ++i)
  {
    printf(" ********** ");
  }
  printf(" **********   ");

}

void print_row_three_or_five_of_cards(int total_cards, card_t** cards)
{
  printf("   *        * ");

  for(int i = 0; i < (total_cards - 2); ++i)
  {
    printf(" *        * ");
  }
 
  printf(" *        *   ");
}

void print_row_four_of_cards(int total_cards, card_t** cards)
{
  if (1 == cards[0]->suit)
  {
    printf("   * CLUBS  * ");
  }
  else if (2 == cards[0]->suit)
  {
    printf("   *DIAMONDS* ");
  }
  else if (3 == cards[0]->suit)
  {
    printf("   * HEARTS * ");
  }
  else if (4 == cards[0]->suit)
  {
    printf("   * SPADES * ");
  }

  for(int i = 1; i < (total_cards - 1); ++i)
  {
    if (1 == cards[i]->suit)
    {
      printf(" * CLUBS  * ");
    }
    else if (2 == cards[i]->suit)
    {
      printf(" *DIAMONDS* ");
    }
    else if (3 == cards[i]->suit)
    {
      printf(" * HEARTS * ");
    }
    else if (4 == cards[i]->suit)
    {
      printf(" * SPADES * ");
    }
  }

  if (1 == cards[4]->suit)
  {
    printf(" * CLUBS  *   ");
  }
  else if (2 == cards[4]->suit)
  {
    printf(" *DIAMONDS*   ");
  }
  else if (3 == cards[4]->suit)
  {
    printf(" * HEARTS *   ");
  }
  else if (4 == cards[4]->suit)
  {
    printf(" * SPADES *   ");
  }
}

void print_row_two_of_cards(int total_cards, card_t** cards)
{
  if (10 < get_visual_rank(cards[0]))
    printf("   *%c       * ", get_visual_rank(cards[0]));
  else if (10 == get_visual_rank(cards[0]))
    printf("   *%d      * ", get_visual_rank(cards[0]));
  else
    printf("   *%d       * ", get_visual_rank(cards[0]));

  for(int i = 1; i < (total_cards - 1); ++i)
  {
    if (10 < get_visual_rank(cards[i]))
      printf(" *%c       * ", get_visual_rank(cards[i]));
    else if (10 == get_visual_rank(cards[i]))
      printf(" *%d      * ", get_visual_rank(cards[i]));
    else
      printf(" *%d       * ", get_visual_rank(cards[i]));
  }

  if (10 < get_visual_rank(cards[4]))
    printf(" *%c       *   ", get_visual_rank(cards[4]));
  else if (10 == get_visual_rank(cards[4]))
    printf(" *%d      *   ", get_visual_rank(cards[4]));
  else
    printf(" *%d       *   ", get_visual_rank(cards[4]));
}

void print_row_six_of_cards(int total_cards, card_t** cards)
{
  if (10 < get_visual_rank(cards[0]))
    printf("   *       %c* ", get_visual_rank(cards[0]));
  else if (10 == get_visual_rank(cards[0]))
    printf("   *      %d* ", get_visual_rank(cards[0]));
  else
    printf("   *       %d* ", get_visual_rank(cards[0]));

  for(int i = 1; i < (total_cards - 1); ++i)
  {
    if (10 < get_visual_rank(cards[i]))
      printf(" *       %c* ", get_visual_rank(cards[i]));
    else if (10 == get_visual_rank(cards[i]))
      printf(" *      %d* ", get_visual_rank(cards[i]));
    else
      printf(" *       %d* ", get_visual_rank(cards[i]));
  }

  if (10 < get_visual_rank(cards[4]))
    printf(" *       %c*   ", get_visual_rank(cards[4]));
  else if (10 == get_visual_rank(cards[4]))
    printf(" *      %d*   ", get_visual_rank(cards[4]));
  else
    printf(" *       %d*   ", get_visual_rank(cards[4]));
}

void print_bottom_edge_of_cards(int total_cards, card_t** cards)
{
  printf("   ********** ");
  for(int i = 0; i < (total_cards - 2); ++i)
  {
    printf(" ********** ");
  }
  printf(" **********   ");
}

void print_row_of_five_cards(card_t** cards)
{
  int total_cards = 5;
  
  // print game table edge boundary
  printf("*");
  print_top_edge_of_cards(total_cards);
  printf("*");
  puts("");

  printf("*");
  print_row_two_of_cards(total_cards, cards);
  printf("*");
  puts("");
  
  /* print row 3 of the cards */
  printf("*");
  print_row_three_or_five_of_cards(total_cards, cards);
  printf("*");
  puts("");

  /* print row 4 of the cards */
  printf("*");
  print_row_four_of_cards(total_cards, cards);
  printf("*");
  puts("");
  
  /* print row 5 of the cards */
  printf("*");
  print_row_three_or_five_of_cards(total_cards, cards);  
  printf("*");
  puts("");
  
  /* print row 6 of the cards */
  printf("*");
  print_row_six_of_cards(total_cards, cards);
  printf("*");
  puts("");
  
  /* print bottom edge of the cards */
  printf("*");
  print_bottom_edge_of_cards(total_cards, cards);
  printf("*");
  puts(""); 
}

void print_row_of_three_cards(card_t** cards)
{
   // print top of cards
  printf("*");
  printf("               ********** ");
  printf(" ********** ");
  printf(" ********** ");
  printf("              *");
  puts("");

  // print row 2 of the cards
  printf("*");

  if (10 < get_visual_rank(cards[0]))
    printf("               *%c       * ", get_visual_rank(cards[0]));
  else if (10 == get_visual_rank(cards[0]))
    printf("               *%d      * ", get_visual_rank(cards[0]));
  else
    printf("               *%d       * ", get_visual_rank(cards[0]));

  if (10 < get_visual_rank(cards[1]))
    printf(" *%c       * ", get_visual_rank(cards[1]));
  else if (10 == get_visual_rank(cards[1]))
    printf(" *%d      * ", get_visual_rank(cards[1]));
  else
    printf(" *%d       * ", get_visual_rank(cards[1]));

  if (10 < get_visual_rank(cards[2]))
    printf(" *%c       * ", get_visual_rank(cards[2]));
  else if (10 == get_visual_rank(cards[2]))
    printf(" *%d      * ", get_visual_rank(cards[2]));
  else
    printf(" *%d       * ", get_visual_rank(cards[2]));

  printf("              *");
  puts("");
  
  // print row 3 of the cards
  printf("*");
  printf("               *        * ");
  printf(" *        * ");
  printf(" *        * ");
  printf("              *");
  puts("");

  // print row 4 of the cards
  printf("*");
  printf("               *DIAMONDS* ");
  printf(" * SPADES * ");
  printf(" * CLOVES * ");
  printf("              *");
  puts("");
  
  // print row 5 of the cards
  printf("*");
  printf("               *        * ");
  printf(" *        * ");
  printf(" *        * ");
  printf("              *");
  puts("");
  
  // print row 6 of the cards
  printf("*");
  if (10 < get_visual_rank(cards[0]))
    printf("               *       %c* ", get_visual_rank(cards[0]));
  else if (10 == get_visual_rank(cards[0]))
    printf("               *      %d* ", get_visual_rank(cards[0]));
  else
    printf("               *       %d* ", get_visual_rank(cards[0]));

  if (10 < get_visual_rank(cards[1]))
    printf(" *       %c* ", get_visual_rank(cards[1]));
  else if (10 == get_visual_rank(cards[1]))
    printf(" *      %d* ", get_visual_rank(cards[1]));
  else
    printf(" *       %d* ", get_visual_rank(cards[1]));

  if (10 < get_visual_rank(cards[2]))
    printf(" *       %c* ", get_visual_rank(cards[2]));
  else if (10 == get_visual_rank(cards[2]))
    printf(" *      %d* ", get_visual_rank(cards[2]));
  else
    printf(" *       %d* ", get_visual_rank(cards[2]));

  printf("              *");
  puts("");
  
  
  // print bottom of the cards
  printf("*");
  printf("               ********** ");
  printf(" ********** ");
  printf(" ********** ");
  printf("              *");
  puts("");

}
