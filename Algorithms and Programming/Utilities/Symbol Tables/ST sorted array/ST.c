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
  int i = st->size++;
  if (st->size > st->maxN) {
    st->a = realloc(st->a, (2*st->maxN)*sizeof(Item));
    if (st->a == NULL)
      return -1;
    st->maxN = 2*st->maxN;
  }
  while( (i>0) && ITEMless(data, st->a[i-1]) ) {
    st->a[i] = st->a[i-1];
    i--;
  }
  st->a[i] = data;
  return i;
}

int STlinsearch(ST st, Key k) {
  int i;
  if (st->size == 0)
    return -1;
  for (i = 0; i  < st->size; i++) {
    if (KEYcompare(k, KEYget(st->a[i]))==0)
      return i;
    if (KEYcompare(k, KEYget(st->a[i]))==-1)
      break;
  }
  return -1;
}
int searchR(ST st, int l, int r, Key k) {
  int m = (l + r)/2;
  if (l > r)
    return -1;
  if (KEYcompare(k, KEYget(st->a[m]))==0)
    return m;
  if (l == r)
    return -1;
  if (KEYcompare(k, KEYget(st->a[m]))==-1)
    return searchR(st, l, m-1, k);
  else
    return searchR(st, m+1, r, k);
}

int STbinsearch(ST st, Key k) {
    return searchR(st, 0, st->size-1, k) ;
}

int STselect(ST st, int r) {
  return r;
}

void STdelete(ST st, Key k) {
  int i, j;
  j = 0;
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

Item  STdisplay_item(ST st, int j) {
  return st->a[j];
}

