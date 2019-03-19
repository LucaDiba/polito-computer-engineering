#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "ST.h"

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


int hash1(Key k, int M) {
  int h = 0, base = 127;
  for ( ; *k != '\0'; k++)
    h = (base * h + *k) % M;
  return h;
}

int hash2(Key k, int M) {
  int h = 0, base = 127;
  for ( ; *k != '\0'; k++)
    h = (base * h + *k);
  h = ((h % 97) + 1) % M;
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
  int i = hash1(KEYget(item), st->M);
  int j = hash2(KEYget(item), st->M);
  while (full(st, i))
    i = (i+j)%st->M;
  st->a[i] = item;
  st->N++;
}

Item STsearch(ST st, Key k) {
  int i = hash1(k, st->M);
  int j = hash2(k, st->M);
    while (full(st, i))
      if (KEYcompare(k, KEYget(st->a[i]))==0)
        return st->a[i];
      else
        i = (i+j)%st->M;
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
  int i = hash1(k, st->M), j = hash2(k, st->M), t;
  Item tmp;
  while (full(st, i))
    if (KEYcompare(k, KEYget(st->a[i]))==0)
      break;
    else
      i = (i+j) % st->M;
  if (ITEMcheckvoid(st->a[i]))
    return;
  st->a[i] = ITEMsetvoid();
  st->N--;
  for (t = i+1; full(st, t); t = (t+1)%st->M, st->N--) {
    tmp = st->a[t];
    st->a[t] = ITEMsetvoid();
    STinsert(st, tmp);
  }
}
