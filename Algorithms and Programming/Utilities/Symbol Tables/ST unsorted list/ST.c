#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "ST.h"

typedef struct STnode* link;
struct STnode { Item data; link next; } ;

struct symboltable { link head; int size; link z; };


link NEW( Item data, link next) {
  link x = malloc(sizeof *x);
  x->data = data;
  x->next = next;
  return x;
}

ST STinit(int maxN) {
  ST st;
  st = malloc(sizeof(*st));
  if(st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->size = 0;
  st->head = (st->z = NEW(ITEMsetvoid(), NULL));
  return st;
}

void STfree(ST st) {
  if (st == NULL)
    return;
  free(st->head);
  free(st);
}

int STcount(ST st) {
  return st->size;
}

void STinsert(ST st, Item data) {
  st->head = NEW(data, st->head);
  st->size++;
}

Item searchR(link t, Key k, link z) {
  if (t == z)
    return ITEMsetvoid();
  if (KEYcompare(KEYget(t->data), k)==0)
    return t->data;
  return searchR(t->next, k, z);
}

Item STsearch(ST st, Key k) {
  return searchR(st->head, k, st->z);
}

link deleteR(link x, Key k) {
  if ( x == NULL )
    return NULL;
  if (KEYcompare(KEYget(x->data), k)==0) {
    link t = x->next;
    free(x);
    return t;
  }
  x->next = deleteR(x->next, k);
  return x;
}

void STdelete(ST st, Key k) {
  st->head = deleteR(st->head, k);
  st->size--;
}

void STdisplay(ST st) {
  link x;
  x = st->head;
  while (x != st->z) {
    ITEMshow(x->data);
    x = x->next;
  }
}
