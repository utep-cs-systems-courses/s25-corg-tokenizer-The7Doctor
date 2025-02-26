#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int space_char(char c) {
  return (c == ' ' || c == '\t');
}

int non_space_char(char c) {
  return (c != ' ' && c != '\t' && c != '\0');
}

char *token_start(char *str) {
  while (*str && space_char(*str)) {
    str++;
  }
  return (*str) ? str : NULL;
}

char *token_terminator(char *token) {
  while (*token && non_space_char(*token)) {
    token++;
  }
  return token;
}

int count_tokens(char *str) {
  int count = 0;
  char *current = token_start(str);

  while (current) {
    count++;
    current = token_terminator(current);
    current = token_start(current);
  }
  return count;
}

char *copy_str(char *inStr, short len) {
  char *copy = malloc((len + 1) * sizeof(char));
  if (!copy) return NULL;

  for(short i; i<len; i++){
      copy[i] = inStr[i];
  }
  copy[len] = '\0';
  return copy;
}

char **tokenize(char *str) {
  int num_tokens = count_tokens(str);
  char **tokens = malloc((num_tokens +1) * sizeof(char*));
  if (!tokens) return NULL;

  char *current = token_start(str);
  int i = 0;

  while (current && i < num_tokens) {
    char *end = token_terminator(current);
    int len = end - current;
    tokens[i++] = copy_str(current, len);
    current = token_start(end);
  }

  tokens[i] = NULL; // Null-terminate the token array
  return tokens;
}

void print_tokens(char **tokens) {
  for (int i = 0; tokens[i]; i++) {
    printf("Token[%d]: %s\n", i, tokens[i]);
  }
}

void free_tokens(char **tokens) {
  for (int i = 0; tokens[i]; i++) {
    free(tokens[i]);
  }
  free(tokens);
}


			  
