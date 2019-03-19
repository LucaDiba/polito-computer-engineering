#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

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

void STfree(ST st) {
  int i;
  for(i=0; i<st->size; i++)
    ITEMfree(st->a[i]);
  if (st->a != NULL)
    free(st->a);
  free(st);
}

int STcount(ST st) {
  return st->size;
}

int STinsert(ST st, Item data) {
  int i = st->size;
  if (st->size >= st->maxN) {
    st->a = realloc(st->a, (2*st->maxN)*sizeof(Item));
    if (st->a == NULL)
      return -1;
    st->maxN = 2*st->maxN;
  }
  st->a[i] = data;
  st->size++;
  return i;
}

int STsearch(ST st, Key k) {
  int i;
  if (st->size == 0)
    return -1;
  for (i = 0; i  < st->size; i++)
    if (KEYcompare(k, KEYget(st->a[i]))==0)
      return i;
  return -1;
}

void STdelete(ST st, Key k) {
  int i, j=0;
  while (KEYcompare(KEYget(st->a[j]), k)!=0)
    j++;
  for (i = j; i < st->size-1; i++)
    st->a[i] = st->a[i+1];
  st->size--;
}

void STdisplay(ST st){
  int i;
  for (i = 0; i < st->size; i++)
    ITEMshow(st->a[i]);
}
