#include "ciphersuite.h"
#include <ctype.h>

/* Static functions */
/* cardgame-specific algorithms */
static void
random_shuffle(tree_t* card_tree, crypto_deck_t* crypto, deck_t* deck)
{
  int card_counter = 0;

  while(card_counter < 52)
  {      
    bool card_assigned = false;
    do
    {
      int random_card_value = (rand() % 16) + 2; /* any value from 2 to 17 */

      tree_node_t * node = get_node(card_tree, random_card_value);
	    
      if(0 < node->list_of_objects->size) /* Verify node key equals card value requested */
      {
	deck_push(deck, pop_back_of_list(node->list_of_objects)); /* transfer card from tree to deck */
	card_assigned = true;
	++card_counter;
      }
    } while (false == card_assigned);
  } /* while */

}

static void
dealer_must_win(tree_t* card_tree, crypto_deck_t* crypto, deck_t* deck)
{
  int card_counter = 0;

  while(card_counter < 52)
  {
    if(0 == (card_counter + 1) % crypto->feedback.period) /* if fourth card in deck (i.e. card for dealer) */
    {
      /* iterate through all card values from 17 to 2 */
      /* and get card with largest value from tree */
      for(int card_value = 17; card_value > 1; --card_value)
      {
	/* Find card value available in data structure of cards */
	tree_node_t * node = get_node(card_tree, card_value);

	if (0 <  node->list_of_objects->size) /* card value found in data structure of cards */
	{
	  deck_push(deck, pop_back_of_list(node->list_of_objects)); /* transfer card from tree to deck */
	  ++card_counter;
	  break;
	}
      } /* for */
    }
    else /* if card is not for dealer */
    {
      bool card_assigned = false;
      int rand_help = 2;
      const int rand_help_increment_frequency = 200;
      int increment_counter = 0;
      
      do
      {
	int random_card_value = (rand() % rand_help) + 2; /* any value from 2 to 17 */

	tree_node_t * node = get_node(card_tree, random_card_value);
	    
	if(0 < node->list_of_objects->size) /* Verify node key equals card value requested */
	{
	  deck_push(deck, pop_back_of_list(node->list_of_objects)); /* transfer card from tree to deck */
	  card_assigned = true;
	  ++card_counter;
	}
	
	if(0 == (++increment_counter % rand_help_increment_frequency))
	{
	  ++rand_help;
	}
	
	if(16 < rand_help)
	  rand_help = 2;
	
      } while (false == card_assigned);

    }
  } /* while */
    
}

/*
  Select the best cards for a player; random card for other players.
  return ordered array of card values

  This function is specifically designed to shuffle (or "encrypt") deck of 52 cards.
 */
void
deck_cipher_encryption(tree_t* card_tree, crypto_deck_t* crypto, deck_t* deck)
{
  if(1 == crypto->key_stream[crypto->feedback.counter % crypto->feedback.period]) /* Dealer should win game */
  {
    dealer_must_win(card_tree, crypto, deck);
  }
  else /* Dealer does not have to win, but may win at random */
  {
    random_shuffle(card_tree, crypto, deck);
  }
  
  ++crypto->feedback.counter; /* increase counter representing total decks shuffled */
}


crypto_t*
initialize_stream_cipher(char (*encryption_algo)(char, crypto_t*),
			 char (*decryption_algo)(char, crypto_t*),
			 keystream_generator* keygen)
		
{  
  crypto_t* crypto = malloc(sizeof(crypto_t));

  crypto->key_stream = (*keygen->generator)(keygen->seed, keygen->length);
  
  crypto->feedback.period = keygen->length;
  crypto->feedback.counter = 0;
  crypto->encrypt = encryption_algo;
  crypto->decrypt = decryption_algo;

  return crypto;
}

crypto_deck_t*
initialize_block_cipher(void (*encryption_algo)(tree_t*, crypto_deck_t*, deck_t*),
		       keystream_generator* keygen)
{
  crypto_deck_t* crypto = malloc(sizeof(crypto_deck_t));
  crypto->key_stream = (*keygen->generator)(keygen->seed, keygen->length);

  crypto->feedback.period = keygen->length;
  crypto->feedback.counter = 0;
  crypto->encrypt = encryption_algo;

  return crypto;
}

keystream_generator*
init_keygen_binary(int total_ones, int period)
{
  keystream_generator* keygen = malloc(sizeof(keystream_generator));
  keygen->generator = &random_binary_permutation;
  keygen->seed = total_ones;
  keygen->length = period;

  return keygen;
}

/* 
   Generate random array of 1s and 0s.  1 = win, 0 = loss.  The array represents
   all contiguous games that will be won or loss by a particular player (i.e. the dealer).
   Each value can be considered as the key that determines a game's outcome.
*/
int*
random_binary_permutation(int total_ones, size_t sequence_length)
{
  int * sequence = calloc(sequence_length, sizeof(int)); /* Create 0 initialized array */
  int ones_counter = 0;
  int num_itr = 0; /* number iterator used for array indexing */

  while(ones_counter < total_ones)   /* Iterate through numbers and assign until complete */
  {
    int binary_value = rand() % 2;

    if((1 == binary_value) && (0 == sequence[num_itr % sequence_length]))
    {
      sequence[num_itr % sequence_length] = binary_value;
      ++ones_counter;
    }

    ++num_itr;
  }

  return sequence;
}

keystream_generator*
init_keygen_primes(int first_prime, int total_primes)
{
  keystream_generator* keygen = malloc(sizeof(keystream_generator));
  keygen->generator = &prime_sieve;
  keygen->seed = first_prime;
  keygen->length = total_primes;

  return keygen;
}

int*
prime_sieve(int first_prime, int total_primes)
{
  if (2 > total_primes || 1 > first_prime)
  {
    return NULL;
  }
  
  /* Create a list of prime numbers ("naive sieve") */
  int primes_found = 0;
  int num_iterator = first_prime; /* keep track of total numbers tested */

  if (1 == first_prime)
  {
    primes_found = 2;
    num_iterator = 3;
  }
  else if (2 == first_prime)
  {
    primes_found = 1;
    num_iterator = 3;
  }

  while (primes_found < total_primes + 1)
  {
    if(1 == num_iterator % 2)
    {
      ++primes_found;
    }
    num_iterator++;
  }

  int * primes = malloc(sizeof(int) * total_primes);
  int primes_index = 0;
  
  for(int i = first_prime; primes_index < total_primes; ++i)
  {
    if(1 == i || 2 == i || 3 == i || 5 == i ||
       7 == i || 11 == i || 13 == i || 17 == i)
    {
      primes[primes_index++] = i;
    }
  }
  
  return primes;
}

char
stream_cipher_encryption_ascii(char plain_char, crypto_t* crypto)
{
  if (!isalpha(plain_char))
  {
    return plain_char;
  }

  int encrypted_char = 0;
  
  if(islower(plain_char))
  {
    int relative_pos = plain_char - 'a'; /* position in alphabet 0-25 */
    int temp = relative_pos + crypto->key_stream[crypto->feedback.counter++ % 8];
    int t2 = temp % 26;
    encrypted_char = 'a' + t2;
  }

  if(isupper(plain_char))
  {
    int relative_pos = plain_char - 'A'; /* position in alphabet 0-25 */
    int temp = relative_pos + crypto->key_stream[crypto->feedback.counter++ % 8];
    int t2 = temp % 26;
    encrypted_char = 'A' + t2;
  }
    
  return encrypted_char;
}

char
stream_cipher_decryption_ascii(char cipher_char, crypto_t* crypto)
{
  if (!isalpha(cipher_char))
  {
    return cipher_char;
  }

  int decrypted_char = 0;
  
  if(islower(cipher_char))
  {
    int shift_amount = crypto->key_stream[crypto->feedback.counter++ % 8];
    int cchar_distance_from_a = cipher_char - 'a'; /* i.e. position in alphabet 0-25 */
    int shifted_cchar_distance_from_z = 25 - (cchar_distance_from_a - shift_amount);
    int distance_from_z = shifted_cchar_distance_from_z % 26;
    decrypted_char = 'z' - distance_from_z;
  }
  else if(isupper(cipher_char))
  {
    int shift_amount = crypto->key_stream[crypto->feedback.counter++ % 8];
    int cchar_distance_from_a = cipher_char - 'a'; /* i.e. position in alphabet 0-25 */
    int shifted_cchar_distance_from_z = 25 - (cchar_distance_from_a - shift_amount);
    int distance_from_z = shifted_cchar_distance_from_z % 26;
    decrypted_char = 'z' - distance_from_z;
  }

  return decrypted_char;  
}

char*
get_input_stream_encrypted(crypto_t* crypto)
{
  getc(stdin); /* clear input stream */
  
  unsigned int buffer_size = 100; /* arbitrary capacity of buffer */

  char* buffer = malloc(sizeof(char) * buffer_size); /* character buffer */

  unsigned int total_chars = 0;

  int c; /* character read from stdin */

  while ('\n' != (c = fgetc(stdin))) /* get chars from stdin stream until new line character is typed */
  {
    if (total_chars + 1 > buffer_size) /* More characters input than buffer size */
    {
      buffer_size += 100; /* increase buffer size by arbitrary value */

      char* temp = realloc(buffer, sizeof(char) * buffer_size); /* extend buffer size */

      buffer = temp;
    }

    buffer[total_chars++] = (*crypto->encrypt)(c, crypto); /* append encrypted character to buffer */
  }

  if (total_chars == 0 && c == EOF) /* No characters in stream */
  {
    free(buffer);
    return NULL;
  }

  /* free unused heap space assigned to buffer */
  char* reduced_buffer = malloc(sizeof(char) * (total_chars + 1));

  /* Copy old, large buffer to new, smaller buffer */
  strncpy(reduced_buffer, buffer, total_chars);
  reduced_buffer[total_chars] = '\0'; /* null-terminate string */

  free(buffer);

  return reduced_buffer;
}

