#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"

struct symboltable { Item *a; int N; int M;};

int STsize(int maxN) {
  int primes[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53 };
  int i = 0, maxNallowed = primes[15]/2;
  if (maxN < maxNallowed) {
    for (i = 0; i<16; i++)
      if (2*maxN <= primes[i])
        return primes[i];
  }
  else
    printf("Too many entries!\n");
  return -1;
}

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

int hash(KEYname k, int M) {
  int h = 0, base = 127;
  for ( ; *k != '\0'; k++)
    h = (base * h + *k) % M;
  return h;
}

/*
int hash(KEYname k, int M) {
  int h = 0;
  h = (*k - 'A' + 1)% M;
  return h;
}
*/

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

int STinsert(ST st, Item item) {
  int i = hash(GETname(item), st->M);
  while (full(st, i))
    i = (i+1)%st->M;
  st->a[i] = item;
  st->N++;
  return i;
}


Item STgetitem(ST st, int i) {
  return st->a[i];
}

int STgetindex(ST st, Item data) {
  int i = hash(GETname(data), st->M);
  while (full(st, i))
    if (CMPname(data, st->a[i]) ==0)
      return i;
    else
      i = (i+1)%st->M;
  return -1;
}

void STdisplay(ST st) {
  int i;
  for (i = 0; i < st->M; i++) {
    printf("st->a[%d] = ", i);
    ITEMshow(st->a[i]);
    printf("\n");
  }
}

void STchange(ST st, Item item) {
  int i = STgetindex(st, item);
  st->a[i] = item;
  return;
}
