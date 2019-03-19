#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

struct item { char *name; };

Item ITEMset(Key k) {
  Item tmp = (Item) malloc(sizeof(Item));
  if (tmp == NULL)
    return ITEMsetvoid();
  else {
    tmp->name = malloc (MAX*sizeof(char));
    strcpy(tmp->name, k);
  }
  return tmp;
}

void ITEMshow(Item data) {
  printf("%s", KEYget(data));
}

Item ITEMsetvoid() {
  char nome[MAX]="";
  Item tmp = (Item) malloc(sizeof(Item));
  if (tmp != NULL)
    tmp->name = strdup(nome);
  return tmp;
}

int ITEMcheckvoid(Item data) {
  if (KEYcmp(KEYget(data), KEYget(ITEMsetvoid()))==0)
    return 1;
  else
    return 0;
}

int KEYcmp(Key key1, Key key2) {
  return strcmp(key1, key2);
}

Key KEYget(Item data) {
  return data->name;
}
