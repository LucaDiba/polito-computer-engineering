#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "IBST.h"

typedef struct IBSTnode* link;
struct IBSTnode { Item item; link l, r; int N; int max; } ;

struct intervalbinarysearchtree { link head; int N; link z; };

link NEW(Item item, link l, link r, int N, int max) {
  link x = malloc(sizeof *x);
  x->item = item; x->l = l; x->r = r; x->N = N; x->max = max;
  return x;
}

void NODEshow(link x) {
  ITEMshow(x->item);
  printf("max = %d\n", x->max);
}

IBST IBSTinit( ) {
  IBST ibst = malloc(sizeof *ibst) ;
  ibst->N = 0;
  ibst->head = ( ibst->z = NEW(ITEMsetvoid(), NULL, NULL, 0, -1));
  return ibst;
}

int IBSTcount(IBST ibst) {
  return ibst->N;
}

int IBSTempty(IBST ibst) {
  if (IBSTcount(ibst) == 0)
    return 1;
  else
    return 0;
}

Item searchR(link h, Item item, link z) {
  if (h == z)
    return ITEMsetvoid();
  if (ITEMoverlap(item, h->item))
    return h->item;
  if (ITEMless_int(item, h->l->max))
    return searchR(h->l, item, z);
  else
    return searchR(h->r, item, z);
  }

Item IBSTsearch(IBST ibst, Item item) {
  return searchR(ibst->head, item, ibst->z);
}

int max (int a, int b, int c) {
  int m = a;
  if (b > m)
    m = b;
  if (c > m)
    m = c;
  return m;
}

link insertR(link h, Item item, link z) {
  if (h == z)
    return NEW(item, z, z, 1, ITEMhigh(item));
  if (ITEMless(item, h->item)) {
    h->l = insertR(h->l, item, z);
    h->max = max(h->max, h->l->max, h->r->max);
  }
  else {
    h->r = insertR(h->r, item, z);
    h->max = max(h->max, h->l->max, h->r->max);
  }
  (h->N)++;
  return h;
}

void IBSTinsert(IBST ibst, Item item) {
  ibst->head = insertR(ibst->head, item, ibst->z);
  ibst->N++;
}

link rotR(link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  x->N = h->N;
  h->N = h->r->N + h->l->N +1;
  h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
  x->max = max(ITEMhigh(x->item), x->l->max, x->r->max);
  return x;
}

link rotL(link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  x->N = h->N;
  h->N = h->l->N + h->r->N +1;
  h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
  x->max = max(ITEMhigh(x->item), x->l->max, x->r->max);
  return x;
}

void sortinorderR(link h, link z) {
  if (h == z)
    return;
  sortinorderR(h->l, z);
  NODEshow(h);
  sortinorderR(h->r, z);
}

void IBSTsortinorder(IBST ibst) {
  sortinorderR(ibst->head, ibst->z);
}

void sortpostorderR(link h, link z) {
  if (h == z)
    return;
  sortpostorderR(h->l, z);
  sortpostorderR(h->r, z);
  NODEshow(h);
}

void IBSTsortpostorder(IBST ibst) {
  sortpostorderR(ibst->head, ibst->z);
}

void sortpreorderR(link h, link z) {
  if (h == z)
    return;
  NODEshow(h);
  sortpreorderR(h->l, z);
  sortpreorderR(h->r, z);
}

void IBSTsortpreorder(IBST ibst) {
    sortpreorderR(ibst->head, ibst->z);
}

link partR(link h, int k) {
  int t  = h->l->N;
  if ( t > k) {
    h->l = partR(h->l, k);
    h = rotR(h);
  }
  if ( t < k) {
    h->r = partR(h->r, k-t-1);
    h = rotL(h);
  }
  return h;
}

link joinLR(link a, link b, link z) {
  if (b == z)
    return a;
  b = partR(b, 0);
  b->l = a;
  b->N = a->N + b->r->N +1;
  b->max = max(ITEMhigh(b->item), a->max, b->r->max);
  return b;
}

link deleteR(link h, Item item, link z) {
  link x;
  if (h == z)
    return z;
  if (ITEMless(item, h->item)) {
    h->l = deleteR(h->l, item, z);
    h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
  }
  if (ITEMless(h->item, item)) {
    h->r = deleteR(h->r, item, z);
    h->max = max(ITEMhigh(h->item), h->l->max, h->r->max);
  }
  (h->N)--;
  if (ITEMeq(item, h->item)) {
    x = h;
    h = joinLR(h->l, h->r, z);
    free(x);
  }
  return h;
}

void IBSTdelete(IBST ibst, Item item) {
  ibst->head = deleteR(ibst->head, item, ibst->z);
  ibst->N--;
}
