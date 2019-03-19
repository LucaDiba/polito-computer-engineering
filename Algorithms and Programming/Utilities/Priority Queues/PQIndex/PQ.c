#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "PQ.h"
#include "ST.h"

struct pqueue { int *A; ST tab; int *qp; int heapsize; };

int LEFT(int i) {
  return i*2+1;
}

int RIGHT(int i) {
  return i*2+2;
}

int PARENT(int i) {
  return (i-1)/2;
}

PQ PQinit(int maxN) {
  int i, size;
  PQ pq = malloc(sizeof(*pq));
  pq->A = malloc(maxN*sizeof(int));
  size = STsize(maxN);
  if (size == -1)
    return NULL;
  printf("ST size = %d\n", size);
  pq->tab = STinit(size);
  pq->qp = malloc(size*sizeof(int));
  for (i=0; i < size; i++)
    pq->qp[i] = -1;
  pq->heapsize = 0;
  return pq;
}

int PQempty(PQ pq){
  return pq->heapsize == 0;
}

int PQsize(PQ pq) {
  return pq->heapsize;
}

void PQinsert (PQ pq, Item item){
  int i, k;
  k = STinsert(pq->tab, item);
  i = pq->heapsize++;
  while ( (i>=1) && (CMPprio(STgetitem(pq->tab, pq->A[PARENT(i)]), item)==-1) ) {
    pq->A[i] = pq->A[PARENT(i)];
    pq->qp[pq->A[i]] = i;
    i = (i-1)/2;
  }
  pq->A[i] = k;
  pq->qp[k] = i;
  return;
}

void Swap(PQ pq, int n1, int n2){
  int temp;

  temp = pq->A[n1];
  pq->A[n1] = pq->A[n2];
  pq->A[n2] = temp;

  n1 = pq->A[n1];
  n2 = pq->A[n2];
  temp = pq->qp[n1];
  pq->qp[n1] = pq->qp[n2];
  pq->qp[n2] = temp;

  return;
}

void Heapify(PQ pq, int i) {
  int l, r, largest;
  l = LEFT(i);
  r = RIGHT(i);
  if (l < pq->heapsize && (CMPprio(STgetitem(pq->tab, pq->A[l]), STgetitem(pq->tab, pq->A[i]))==1))
    largest = l;
  else
    largest = i;
  if (r < pq->heapsize && (CMPprio(STgetitem(pq->tab, pq->A[r]), STgetitem(pq->tab, pq->A[largest]))==1))
    largest = r;
  if (largest != i) {
    Swap(pq, i,largest);
	Heapify(pq, largest);
  }
  return;
}

Item PQextractMax(PQ pq) {
  Item item;
  Swap (pq, 0, pq->heapsize-1);
  item = STgetitem(pq->tab, pq->A[pq->heapsize-1]);
  pq->heapsize--;
  Heapify(pq, 0);
  return item;
}

Item PQshowMax(PQ pq){
  return STgetitem(pq->tab, pq->A[0]);
}

void PQdisplay(PQ pq, int maxN){
  int i;
  printf("priority queue\n");
  for (i = 0; i < pq->heapsize; i++) {
    printf("pq->A[%d] = %d\n", i, pq->A[i]);
    ITEMshow(STgetitem(pq->tab, pq->A[i]));
  }
  printf("PQ: indices\n");
  for (i = 0; i < pq->heapsize; i++)
    printf("%d  ", pq->A[i]);
  printf("\n");
  printf("QP: reverse indices\n");
  for (i = 0; i < STsize(maxN); i++)
    printf("%d  ", pq->qp[i]);
  printf("\n");
}

void PQchange (PQ pq, Item item) {
  int pos = pq->qp[STgetindex(pq->tab, item)];
  int temp = pq->A[pos];

  while ( (pos>=1) && (CMPprio(STgetitem(pq->tab, pq->A[PARENT(pos)]), item)==-1) ) {
    pq->A[pos] = pq->A[PARENT(pos)];
    pq->qp[pq->A[pos]] = pos;
    pos = (pos-1)/2;
  }
  pq->A[pos] = temp;
  pq->qp[temp] = pos;

  STchange(pq->tab, item);
  Heapify(pq, pos);
  return;
}

