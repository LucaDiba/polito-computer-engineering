#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"
#define c1 0
#define c2 1

struct symboltable { Item *a; int N; int M;};

ST STinit(int maxN) {
  int i;
  ST st = malloc(sizeof(*st));
  st->N = 0;
  st->M = maxN;
  st->a = malloc(st->M * sizeof(Item) );
  for (i = 0; i < st->M; i++)
    st->a[i] = ITEMsetvoid();
  return st;
}

int hash(Key k, int M) {
  int h = 0, base = 127;
  for ( ; *k != '\0'; k++)
    h = (base * h + *k-64) % M;
  return h;
}
/*
int hash(Key k, int M) {
  int h = 0, base = 127;
  for ( ; *k != '\0'; k++)
    h = (base * h + *k) % M;
  return h;
}
*/

int hashU( char *k, int M) {
  int h, a = 31415, b = 27183;
  for ( h = 0; *k != '\0'; k++, a = a*b % (M-1))
    h = (a*h + *k) % M;
  return h;
}

int STcount(ST st) {
  return st->N;
}

int STempty(ST st) {
  if ( STcount(st) == 0)
    return 1;
  else
    return 0;
}

int full(ST st, int i) {
  if (ITEMcheckvoid(st->a[i]))
    return 0;
  else
    return 1;
}

void STinsert(ST st, Item item) {
  int i = 0;
  int start = hash(KEYget(item), st->M);
  int index = start;
  while (full(st, index)) {
    i++;
    index = (start + c1*i + c2*i*i)%st->M;
  }
  st->a[index] = item;
  st->N++;
}

Item STsearch(ST st, Key k) {
  int i = 0;
  int start = hash(k, st->M);
  int index = start;
  while (full(st, index))
    if (KEYcompare(k, KEYget(st->a[index]))==0)
      return st->a[index];
    else {
      i++;
      index = (start + c1*i + c2*i*i)%st->M;
    }
  return ITEMsetvoid();
}

void STdisplay(ST st) {
  int i;
  for (i = 0; i < st->M; i++) {
    printf("st->a[%d] = ", i);
    ITEMshow(st->a[i]);
    printf("\n");
  }
}
void STdelete(ST st, Key k) {
  int i=0, j, start = hash(k, st->M), index = start;
  Item tmp;
  while (full(st, index))
    if (KEYcompare(k, KEYget(st->a[index]))==0)
      break;
    else {
      i++;
      index = (start + c1*i + c2*i*i)%st->M;
    }
  if (ITEMcheckvoid(st->a[index]))
    return;
  st->a[index] = ITEMsetvoid();
  st->N--;
  i = 1;
  for (j = (index + c1*i + c2*i*i)%st->M; full(st, j); j = (index + c1*i + c2*i*i)%st->M, st->N--) {
    tmp = st->a[j];
    st->a[j] = ITEMsetvoid();
    STinsert(st, tmp);
    i++;
  }
}

