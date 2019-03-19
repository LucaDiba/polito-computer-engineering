#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

struct symboltable { Item *a; int maxN; int size;};

ST STinit(int maxN) {
  ST st;
  int i;
  st = malloc(sizeof(*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->a = malloc(maxN * sizeof(Item) );
  for (i = 0; i < maxN; i++)
    st->a[i] = ITEMsetvoid();
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
  int index = getindex(KEYget(data));
  st->a[index] = data;
  st->size++;
  return index;
}

int STsearch(ST st, Key k) {
  int index = getindex(k);
  if (ITEMcheckvoid(st->a[index]))
    return -1;
  return index;
}

void STdelete(ST st, Key k) {
  st->a[getindex(k)] = ITEMsetvoid();
  st->size--;
}

int STselect(ST st, int r) {
  int i;
  for (i = 0; i < st->maxN; i++)
    if ( (ITEMcheckvoid(st->a[i])==0) && (r-- == 0))
      return getindex(KEYget(st->a[i]));
  return -1;
}

void STdisplay(ST st){
  int i;
  for (i = 0; i < st->maxN; i++)
    if (ITEMcheckvoid(st->a[i])==0)
      ITEMshow(st->a[i]);
}

Item  STdisplay_item(ST st, int j) {
  return st->a[j];
}
