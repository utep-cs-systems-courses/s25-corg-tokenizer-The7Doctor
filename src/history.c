#include <stdio.h>
#include <stdlib.h>
#include "history.h"

List* init_history() {
  List *list = (List *)malloc(sizeof(List));
  if (!list) return NULL;
  list->root = NULL;
  return list;
}

void add_history(List *list, char *str) {
  if (!list || !str) return;

  Item *new_item = (Item *)malloc(sizeof(Item));
  if (!new_item) return;

  new_item->id = (list->root == NULL) ? 1 : list->root->id + 1;

  int len = 0;
  while (str[len] != '\0') len++;

  new_item->str = (char *)malloc(len + 1);
  if (!new_item->str) {
    free(new_item);
    return;
  }

  for (int i = 0; i < len; i++) {
    new_item->str[i] = str[i];
  }
  new_item->str[len] = '\0';

  new_item->next = list->root;
  list->root = new_item;
}

char *get_history(List *list, int id) {
  if (!list) return NULL;

  Item *current = list->root;
  while (current) {
    if (current->id == id) {
      return current->str;
    }
    current = current->next;
  }
  return NULL;
}

void print_history(List *list) {
  if (!list) return;

  Item *current = list->root;
  while (current) {
    printf("%d: %s\n", current->id, current->str);
    current = current->next;
  }
}

void free_history(List *list) {
  if (!list) return;

  Item *current = list->root;
  while (current) {
    Item *next = current->next;
    free(current->str);
    free(current);
    current = next;
  }
  free(list);
}
