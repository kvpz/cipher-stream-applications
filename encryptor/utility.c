#include "utility.h"


void
clear_terminal_screen()
{
  for(int i = 0; i < 100; ++i)
  {
    puts("");
  }
}

void
print_string_with_spaces(char* str)
{
  for(int i = 0; i < strlen(str); ++i)
  {
    printf("%c   ", str[i]);
  }
}

void
print_string_to_ascii(char* str)
{
  for(int i = 0; i < strlen(str); ++i)
  {
    if(99 < str[i])
      printf("%d ", str[i]);
    else
      printf("%d  ", str[i]);
  }
}

char*
get_stdin_stream()
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

    buffer[total_chars++] = c; /* append character to buffer */
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
