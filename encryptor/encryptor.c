/*
  encryptor.cpp
  Kevin Perez

  Encryption and decryption of ASCII characters.
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "ciphersuite.h"
#include "utility.h"

static void display_menu(void);
static void menu_option_a(void);
static void menu_option_b(void);
static void print_encryption_results(crypto_t*, char*);
static void print_decryption_results(crypto_t*, char*);
static void print_results(crypto_t*, char*);
static void destruct_heap(crypto_t*, char*);
  
int main(void)
{
  printf("\n     "
	 "String Encryption Program\n"
	 "     =========================\n");
  display_menu();
  
  char menu_option;

  /* Loop main menu prompt */
  do {
    printf("Type a letter corresponding to a menu option, then press ENTER: ");
    scanf("%c", &menu_option);

    switch(menu_option)
    {
      case 'a':
      case 'A':
	menu_option_a();
	break;
      case 'b':
      case 'B':
	menu_option_b();
	break;
    }    
  } while (menu_option != 'q' && menu_option != 'Q');

  return 0;
}

void display_menu()
{
  printf("\n"
	 "\t(A) Encrypt a string\n"
	 "\t(B) Decrypt a string\n"
	 "\t(Q) Quit\n\n");
}

static void
menu_option_a()
{
  puts("Type in a string of ASCII characters then press ENTER to encrypt.");
  printf("\nPlaintext: ");

  int first_prime = 1;
  int total_primes = 8;
  keystream_generator* keygen = init_keygen_primes(first_prime, total_primes);

  crypto_t* cryptosystem = initialize_stream_cipher(cipher_algorithms.stream_cipher_encryption_ascii,
						    cipher_algorithms.stream_cipher_decryption_ascii,
						    keygen);

  char * ciphertext = get_input_stream_encrypted(cryptosystem);
  
  print_encryption_results(cryptosystem, ciphertext);

  destruct_heap(cryptosystem, ciphertext);
}

static void
menu_option_b()
{
  puts("Type in ciphertext then press ENTER to decrypt.");
  printf("\nciphertext: ");

  int first_prime = 1;
  int total_primes = 8;
  keystream_generator* keygen = init_keygen_primes(first_prime, total_primes);

  crypto_t* cryptosystem = initialize_stream_cipher(cipher_algorithms.stream_cipher_encryption_ascii,
						    cipher_algorithms.stream_cipher_decryption_ascii,
						    keygen);

  char * ciphertext = get_stdin_stream();

  print_encryption_results(cryptosystem, ciphertext);

  destruct_heap(cryptosystem, ciphertext);
}

static void
print_encryption_results(crypto_t* cryptosystem, char* ciphertext)
{
  puts("\n\tEncryption Results");
  print_results(cryptosystem, ciphertext);
}

static void
print_decryption_results(crypto_t* cryptosystem, char* ciphertext)
{
  puts("\n\tDecryption Results");
  print_results(cryptosystem, ciphertext);
}

static void
print_results(crypto_t* cryptosystem, char* ciphertext)
{
  printf("              Plaintext: ");

  cryptosystem->feedback.counter = 0;
  for(int i = 0; i < strlen(ciphertext); ++i)
  {
    char c = cryptosystem->decrypt(ciphertext[i], cryptosystem);
    printf("%c   ", c);
  }

  printf("\n Plaintext ASCII Values: ");
  cryptosystem->feedback.counter = 0;
  for(int i = 0; i < strlen(ciphertext); ++i)
  {
    char c = cryptosystem->decrypt(ciphertext[i], cryptosystem);
    if(99 < c)
      printf("%d ", c);
    else
      printf("%d  ", c);
  }

  printf("\n             Ciphertext: ");
  print_string_with_spaces(ciphertext);
  puts("");
  
  printf("Ciphertext ASCII Values: ");
  print_string_to_ascii(ciphertext);  

  printf("\n       Prime value keys: ");
  cryptosystem->feedback.counter = 0;
  for(int i = 0; i < strlen(ciphertext); ++i)
  {
    int prime_key = 0;
    if(ciphertext[i] != cryptosystem->decrypt(ciphertext[i], cryptosystem))
    {
      prime_key = cryptosystem->key_stream[(cryptosystem->feedback.counter - 1) % 8];
    }
    if(9 < prime_key)
      printf("%d  ", prime_key);
    else
      printf("%d   ", prime_key);
  }

  puts("\n\n");
}

static void
destruct_heap(crypto_t* cryptosystem, char* ciphertext)
{
  free(ciphertext);
  free(cryptosystem->key_stream);
  free(cryptosystem);
}
