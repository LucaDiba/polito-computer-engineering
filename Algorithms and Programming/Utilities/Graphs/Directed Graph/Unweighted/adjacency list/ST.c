#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"


typedef struct item_ { char *str; } Item;

static char *KEYget(Item data) {
    return data.str;
}

static Item ITEMnew(char *str) {
    Item data;
    data.str = strdup(str);
    return data;
}
struct symboltable { Item *a; int maxN; int size;};

ST STinit(int maxN) {
  ST st;
  st = malloc(sizeof(*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->a = malloc(maxN * sizeof(Item) );
  st->maxN = maxN;
  st->size = 0;
  return st;
}

int STcount(ST st) {
  return st->size;
}

int STinsert(ST st, char *data) {
  int i = st->size++;
  if (st->size > st->maxN) {
    st->a = realloc(st->a, (2*st->maxN)*sizeof(Item));
    if (st->a == NULL)
      return -1;
    st->maxN = 2*st->maxN;
  }
  st->a[i] = ITEMnew(data);
  return i;
}


int STsearch(ST st, char *data) {
  int i;
  if (st->size == 0)
    return -1;
  for (i = 0; i  < st->size; i++)
    if (strcmp(data, KEYget(st->a[i]))==0)
      return i;
  return -1;
}

char * STretrieve(ST st, int i){
  return KEYget(st->a[i]);
}

