#include <stdlib.h>
#include "Item.h"
#include "PQ.h"

struct pqueue { Item *array; int heapsize; };

int LEFT(int i) {
  return i*2+1;
}

int RIGHT(int i) {
  return i*2+2;
}

int PARENT(int i) {
  return (i-1)/2;
}

PQ PQinit(int maxN){
  PQ pq;
  pq = malloc(sizeof(*pq));
  pq->array = (Item *)malloc(maxN*sizeof(Item));
  pq->heapsize = 0;
  return pq;
}

int PQempty(PQ pq) {
  return pq->heapsize == 0;
}

int PQsize(PQ pq) {
  return pq->heapsize;
}

void PQinsert (PQ pq, Item item) {
  int i;
  i  = pq->heapsize++;
  while( (i>=1) && (ITEMless(pq->array[PARENT(i)], item)) ) {
    pq->array[i] = pq->array[PARENT(i)];
    i = (i-1)/2;
  }
  pq->array[i] = item;
  return;
}

void Swap(PQ pq, int n1, int n2) {
  Item temp;

  temp  = pq->array[n1];
  pq->array[n1] = pq->array[n2];
  pq->array[n2] = temp;
  return;
}


void Heapify(PQ pq, int i) {
  int l, r, largest;
  l = LEFT(i);
  r = RIGHT(i);
  if ( (l < pq->heapsize) && (ITEMgreater(pq->array[l], pq->array[i])) )
    largest = l;
  else
    largest = i;
  if ( (r < pq->heapsize) && (ITEMgreater(pq->array[r], pq->array[largest])))
    largest = r;
  if (largest != i) {
    Swap(pq, i,largest);
	Heapify(pq, largest);
  }
  return;
}

Item PQextractMax(PQ pq) {
  Item item;
  Swap (pq, 0,pq->heapsize-1);
  item = pq->array[pq->heapsize-1];
  pq->heapsize--;
  Heapify(pq, 0);
  return item;
}

Item PQshowMax(PQ pq) {
  return pq->array[0];
}

void PQdisplay(PQ pq) {
  int i;
  for (i = 0; i < pq->heapsize; i++)
    ITEMshow(pq->array[i]);
}

void PQchange (PQ pq, int pos, Item item) {
  while( (pos>=1) && (ITEMless(pq->array[PARENT(pos)], item)) ) {
    pq->array[pos] = pq->array[PARENT(pos)];
	pos = (pos-1)/2;
  }
  pq->array[pos] = item;
  Heapify(pq, pos);
  return;
}
