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
  st->z = NEW(ITEMsetvoid(), NULL);
  st->head = NEW(ITEMsetvoid(), st->z);
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
  link x, t;
  t = malloc(sizeof(link));
  t->data = data;
  t->next = NULL;

  for (x = st->head; x->next != st->z; x = x->next)
    if (ITEMgreater(x->next->data, data))
      break;
  t->next = x->next;
  x->next = t;
  st->size++;

}

Item STsearch(ST st, Key k) {
  link x;
  for (x = st->head->next; x != st->z; x = x->next)
    if (KEYcompare( KEYget(x->data), k) ==0)
      return x->data;
  return ITEMsetvoid();
}

void STdelete(ST st, Key k) {
  link x;
  for (x = st->head; x->next != st->z; x = x->next)
    if (KEYcompare( KEYget(x->next->data), k) ==0)
      x->next = x->next->next;
  return;
}

Item  STselect(ST st, int r) {
  int i;
  link x = st->head;
  for (i = r; i>=0; i--)
    x = x->next;
  return x->data;
}


void STdisplay(ST st) {
  link x;
  for (x = st->head->next; x != st->z; x = x->next)
    ITEMshow(x->data);
}
