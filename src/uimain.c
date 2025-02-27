#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"



#define MAX_INPUT_SIZE 256



int compareStr(const char *s1, const char *s2) {

  while (*s1 && *s2 && *s1 == *s2) {

    s1++;

    s2++;

  }

  return *(unsigned char *)s1 - *(unsigned char *)s2;

}



int strToInt(const char *str) {

  int num = 0;

  while (*str >= '0' && *str <= '9') {

    num = num * 10 + (*str - '0');

    str++;

  }

  return num;

}



int main() {

  char input[MAX_INPUT_SIZE];

  char **tokens;

  List *history = init_history();



  while (1) {

    printf("Enter a string to tokenize (or type 'exit' to quit, 'history' to view history, or '!<id>' to recall an entry):\n");

    if (!fgets(input, MAX_INPUT_SIZE, stdin)) {

      printf("Error reading input.\n");

      continue;

    }


    int len = 0;
    while (input[len] != '\0' && input[len] != '\n') len++;
    input[len] = '\0';

    if (compareStr(input, "exit") == 0) break;
    if (compareStr(input, "history") == 0) {
      print_history(history);
      continue;
    }

    if (input[0] == '!' && input[1] != '\0') {
      int id = strToInt(input + 1);
      char *history_entry = get_history(history, id);
      if (history_entry) {
	printf("Recalling: %s\n", history_entry);
	add_history(history, history_entry);
	tokens = tokenize(history_entry);
	print_tokens(tokens);
	free_tokens(tokens);
      } else {
	printf("No history entry found for id %d\n", id);
      }
      continue;
    }

    add_history(history, input);
    tokens = tokenize(input);
    printf("Tokenized output:\n");
    print_tokens(tokens);
    free_tokens(tokens);
  }

  printf("History of inputs:\n");
  print_history(history);
  free_history(history);
  printf("Exiting program.\n");
  return 0;
}
