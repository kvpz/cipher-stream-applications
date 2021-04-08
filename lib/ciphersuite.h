#ifndef Header_ciphersuite
#define Header_ciphersuite
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "deck.h"

typedef struct feedback_register_t feedback_register_t;
typedef struct keystream_generator keystream_generator;
typedef struct crypto_t crypto_t;
typedef struct crypto_deck_t crypto_deck_t;

struct feedback_register_t
{
  int period; // this is equal to the amount of keys
  int counter; // Preserves the last state of the key_stream at the position of a char in plaintext
};

/* keystream generator factory structures */
struct keystream_generator
{
  int* (*generator)(int, int);
  int seed;
  int length;
};

/* cryptosystem structure */
struct crypto_t
{
  int* key_stream;  
  feedback_register_t feedback; // cfb;
  char (*encrypt)(char, crypto_t*);
  char (*decrypt)(char, crypto_t*);
};

struct crypto_deck_t
{
  int* key_stream;  
  feedback_register_t feedback; // cfb;
  void (*encrypt)(tree_t*, crypto_deck_t*, deck_t*);
};

/* Constructor functions */
crypto_t* initialize_stream_cipher(char (*encrypt)(char, crypto_t*),
				   char (*decrypt)(char, crypto_t*),
				   keystream_generator*);
crypto_deck_t* initialize_block_cipher(void (*encryption_algo)(tree_t*, crypto_deck_t*, deck_t*),
				       keystream_generator*);
keystream_generator* init_keygen_primes(int, int);
keystream_generator* init_keygen_binary(int, int);

/* Encryption functions */
char stream_cipher_encryption_ascii(char, crypto_t*);
char stream_cipher_decryption_ascii(char, crypto_t*);
void deck_cipher_encryption(tree_t*, crypto_deck_t*, deck_t*);

/* I/O functions */
char* get_input_stream_encrypted(crypto_t*);

/* key generators */
int* prime_sieve(int, int);
int* random_binary_permutation(int, size_t);

/* Function pointer tables */
static struct cipher_algorithms
{
  char (*stream_cipher_encryption_ascii)(char, crypto_t*);
  char (*stream_cipher_decryption_ascii)(char, crypto_t*);
  void (*deck_cipher_encryption)(tree_t*, crypto_deck_t*, deck_t*);
} cipher_algorithms = {
  &stream_cipher_encryption_ascii,
  &stream_cipher_decryption_ascii,
  &deck_cipher_encryption
};

#endif
