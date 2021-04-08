#include <stdio.h>
#include "ciphersuite.h"
#include "linkedlist.h"
#include "deck.h"
#include "card.h"
#include "player.h"
#include "shuffler.h"
#include "utility.h"

/* function prototypes */
static void show_main_menu(void);
static void show_in_game_menu(void);
static void show_splash_screen(void);
static void four_person_game(void);
static void eight_person_game(void);
static void play_one_four_person_round(crypto_deck_t*, int*);
static void play_one_eight_person_round(crypto_deck_t*, int*);
static void calculate_and_announce_winner(player_t**, int);
static void hand_out_cards(player_t**, deck_t*, int);
static void free_heap_memory(deck_t*, player_t**, int);

int main(void)
{
  show_splash_screen();
  show_main_menu();

  char menu_option = 0;

  do
  {
    printf("Type a letter corresponding to a menu option, then press ENTER: ");
    scanf(" %c", &menu_option);
    
    switch(menu_option)
    {
      case 'a':
      case 'A':
	four_person_game();
	clear_terminal_screen();
	show_main_menu();
	break;
      case 'b':
      case 'B':
	eight_person_game();
	clear_terminal_screen();
	show_main_menu();
	break;
      case 'q':
      case 'Q':
	break;
      default:
	puts("Invalid menu option. Try again\n");
    }
  } while ('q' != menu_option && 'Q' != menu_option);

  return 0;
}

static void
show_splash_screen()
{
  puts("");
  puts("\t\tBiased Cardgame Emulator");
  puts("\t\t========================\n");
}

static void
show_main_menu()
{
  printf("\n"
	 "\t**************************************************\n"
	 "\t|| ~~~~~~~~~~~~~~~~ MAIN MENU ~~~~~~~~~~~~~~~~~ ||\n"
	 "\t|| (A) Play 4 person game                       ||\n"
	 "\t|| (B) Play 8 person game                       ||\n"
	 "\t|| (Q) Quit program                             ||\n"
	 "\t**************************************************\n\n");
}

static void
show_in_game_menu()
{
  printf("\n"
	 "\t**************************************************\n"
	 "\t|| ~~~~~~~~~~~~~~~ IN-GAME MENU ~~~~~~~~~~~~~~~ ||\n"
	 "\t|| (A) Play one round                           ||\n"
	 "\t|| (E) Back to Main Menu                        ||\n"
	 "\t**************************************************\n\n");
}

static void
four_person_game()
{
  clear_terminal_screen();
  show_in_game_menu();

  int games_played_consecutively = 0;
  int dealer_wins = 0;
  int total_four_player_games = 0;
  
  /* Configure keystream generator for cipher */
  const int dealer_total_wins = 3;
  const int sample_space = 4; /* Dealer must win 3 out of 4 games */
  keystream_generator * keygen = init_keygen_binary(dealer_total_wins, sample_space);

  /* Initialize cipher */
  crypto_deck_t * crypto = initialize_block_cipher(cipher_algorithms.deck_cipher_encryption,
					      keygen);

  char menu_option;
  do {
    printf("Type a letter corresponding to a menu option, then press ENTER: ");
    scanf(" %c", &menu_option);
    
    switch(menu_option)
    {
      case 'a':
      case 'A':
	play_one_four_person_round(crypto, &dealer_wins);
	++games_played_consecutively;
	break;
      case 'e':
      case 'E':
	break;
      default:
	puts("Invalid input.  Try again\n");
    }
    
    printf("\tDealer win ratio: %f\n", (float)dealer_wins / (float)++total_four_player_games);
    printf("\tTotal games played: %d\n\n", games_played_consecutively);

    /* reinitialize crypto after every four games so key is different */
    if (0 == games_played_consecutively % 4)
    {
      keystream_generator * keygen = init_keygen_binary(dealer_total_wins, sample_space);
      crypto = initialize_block_cipher(cipher_algorithms.deck_cipher_encryption,
				       keygen);
    }
  } while ('e' != menu_option && 'E' != menu_option);

  free(keygen);
  free(crypto);
}

static void
play_one_four_person_round(crypto_deck_t* crypto, int * dealer_wins)
{
  clear_terminal_screen();
  
  int total_players = 4;
  player_t * players[total_players];
  
  for(int id = 0; id < total_players; ++id)
  {
    players[id] = initialize_new_player(id);
  }

  deck_t * deck = deck_initialize_with_cards();

  /* Shuffle deck so dealer should have a 75% chance of winning */
  biased_fisher_yates_shuffle(deck, crypto);

  hand_out_cards(players, deck, total_players);
  
  print_player_cards(players[0]);
  print_player_cards(players[1]);
  print_player_cards(players[2]);
  print_player_cards(players[3]);

  calculate_and_announce_winner(players, total_players);

  if (players[0]->winner == true)
    ++(*dealer_wins);

  free_heap_memory(deck, players, total_players);
}

void
calculate_and_announce_winner(player_t** players, int total_players)
{
  int highest_score = 0;
  int total_winners = 0;

  puts("");
  for(int i = 0; i < total_players; ++i)
  {
    if (players[i]->hand_total_value >= highest_score)
    {
      highest_score = players[i]->hand_total_value;
    }
  }
  
  for(int i = 0; i < total_players; ++i)
  {
    if (highest_score == players[i]->hand_total_value)
    {
      printf("\tPLAYER #%d WON\n", players[i]->id);
      players[i]->winner = true;
      ++total_winners;
    }
  }

  if (1 < total_winners)
  {
    puts("\tThere was a TIE!");
  }
  puts("");
}

static void
eight_person_game()
{
  clear_terminal_screen();
  show_in_game_menu();

  int games_played_consecutively = 0;
  int dealer_wins = 0;
  int total_eight_player_games = 0;
  
  /* Configure keystream generator for cipher */
  const int dealer_total_wins = 3;
  const int sample_space = 8; /* Dealer must win 3 out of 8 games */
  keystream_generator * keygen = init_keygen_binary(dealer_total_wins, sample_space);

  /* Initialize cipher */
  crypto_deck_t * crypto = initialize_block_cipher(cipher_algorithms.deck_cipher_encryption,
					      keygen);

  char menu_option;
  do {
    printf("Type a letter corresponding to a menu option, then press ENTER: ");
    scanf(" %c", &menu_option);
    
    switch(menu_option)
    {
      case 'a':
      case 'A':
	play_one_eight_person_round(crypto, &dealer_wins);
	++games_played_consecutively;
	break;
      case 'e':
      case 'E':
	break;
      default:
	puts("Invalid input.  Try again\n");
    }

    printf("\tDealer win ratio: %f\n", (float)dealer_wins / (float)++total_eight_player_games);
    printf("\tTotal games played: %d\n\n", games_played_consecutively);
    
    /* reinitialize crypto after every eight games so key is different */
    if (0 == games_played_consecutively % 8)
    {
      keystream_generator * keygen = init_keygen_binary(dealer_total_wins, sample_space);
      crypto = initialize_block_cipher(cipher_algorithms.deck_cipher_encryption,
				       keygen);
    }
  } while ('e' != menu_option && 'E' != menu_option);

  free(keygen);
  free(crypto);
}


static void
play_one_eight_person_round(crypto_deck_t* crypto, int* dealer_wins)
{
  clear_terminal_screen();
  
  int total_players = 8;
  player_t * players[total_players];
  
  for(int id = 0; id < total_players; ++id)
  {
    players[id] = initialize_new_player(id);
  }

  deck_t * deck = deck_initialize_with_cards();

  /* Shuffle deck so dealer should have a 37.5% chance of winning */
  biased_fisher_yates_shuffle(deck, crypto);

  /* throw away four cards */
  deck_pop(deck);
  deck_pop(deck);
  deck_pop(deck);
  deck_pop(deck);

  hand_out_cards(players, deck, total_players);

  print_cards_eight_player_game(players[0]);
  print_cards_eight_player_game(players[1]);
  print_cards_eight_player_game(players[2]);
  print_cards_eight_player_game(players[3]);
  print_cards_eight_player_game(players[4]);
  print_cards_eight_player_game(players[5]);
  print_cards_eight_player_game(players[6]);
  print_cards_eight_player_game(players[7]);
  
  calculate_and_announce_winner(players, total_players);

  if (true == players[0]->winner)
    ++(*dealer_wins);
  
  free_heap_memory(deck, players, total_players);
}

static void
hand_out_cards(player_t** players, deck_t* deck, int total_players)
{
  int cards_per_player = 52 / total_players;
  
  /* give players cards from deck, one card per person per iteration */
  for(int i = 0; i < cards_per_player; ++i)
  {
    for(int p = 0; p < total_players; ++p)
    {
      get_card_from_deck(players[p], deck);
    }
  }
}

void
free_heap_memory(deck_t* deck, player_t** players, int total_players)
{
  free(deck); /* All cards should have already been popped and freed from deck */
  
  for(int i = 0; i < total_players; ++i)
  {
    /* 1. Free all cards in players' hand */
    list_node_t * node = players[i]->hand->root;
    while (node->next)
    {
      node = node->next;
      free(node->previous->object);
      free(node->previous);
    }

    free(node->object);
    free(node);

    /* 2. Free player's hand */
    free(players[i]->hand);

    /* 3. Free player */
    free(players[i]);
  }
}
