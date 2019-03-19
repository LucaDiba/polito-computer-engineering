#include <stdlib.h>
#include <stdio.h>
#include "PQ.h"

struct pqueue {
    int *array, *qp, heapsize;
};
/* Item: int */
typedef int Item;
int ITEMgreater(Item a, Item b){
    return a > b;
}
int ITEMless(Item a, Item b){
    return a < b;
}
void ITEMshow(Item a){
    printf("%d", a);
}


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
  pq->array = malloc(maxN * sizeof(Item));
  pq->qp    = malloc(maxN * sizeof(Item));
  pq->heapsize = 0;
  return pq;
}

int PQempty(PQ pq) {
  return pq->heapsize == 0;
}

int PQsize(PQ pq) {
  return pq->heapsize;
}

void Swap(PQ pq, int n1, int n2) {
    int tmp = pq->array[n1];
    int tmp1 = pq->qp[pq->array[n1]];

    pq->qp[pq->array[n1]] = pq->qp[pq->array[n2]];
    pq->qp[pq->array[n2]] = tmp1;

    pq->array[n1] = pq->array[n2];
    pq->array[n2] = tmp;
}

void fixUp(PQ pq, int k, int *min_dist) {
    int i;
    i = pq->qp[k];
    if (pq->heapsize == 1 || i == 0 || min_dist[k] >= min_dist[pq->array[PARENT(i)]])
        return;
    Swap(pq, i, PARENT(i));
    fixUp(pq, k, min_dist);
}

void fixDown(PQ pq, int k, int *min_dist) {
    int j, i;
    i = pq->qp[k];
    if (LEFT(i) >= pq->heapsize || RIGHT(i) >= pq->heapsize)
        return;
    if (min_dist[k] <= min_dist[pq->array[LEFT(i)]] && min_dist[k] <= min_dist[pq->array[RIGHT(i)]])
        return;
    if (min_dist[pq->array[LEFT(i)]] >= min_dist[pq->array[RIGHT(i)]])
        j = RIGHT(i);
    else
        j = LEFT(i);
    Swap(pq, i, j);
    fixDown(pq, k, min_dist);
}

void PQinsert(PQ pq, int *min_dist, int k) {
    pq->qp[k] = pq->heapsize++;
    pq->array[pq->qp[k]] = k;
    fixUp(pq, k, min_dist);
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
}

Item PQextractMin(PQ pq, int *min_dist) {
    Item item;

    Swap (pq, 0,pq->heapsize-1);
    item = pq->array[pq->heapsize-1];
    pq->heapsize--;

    fixDown(pq, pq->array[0], min_dist);
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

void PQchange(PQ pq, int *min_dist, int k) {
    fixDown(pq, k, min_dist);
    fixUp(pq, k, min_dist);
}