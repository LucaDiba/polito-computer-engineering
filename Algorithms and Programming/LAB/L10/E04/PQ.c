#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>

#define PARENT(i)  (((i)-1)/2)
#define LEFT(i)    (((i)*2)+1)
#define RIGHT(i)   (((i)*2)+2)



void swap(PQ pq, int i, int j) {
  Item tmp = pq->A[i];
  pq->A[i] = pq->A[j];
  pq->A[j] = tmp;
}

int getIndex(PQ pq, Item k){
    int i;
    for(i=0; i<pq->heapsize; i++)
        if(k.r == pq->A[i].r && k.c == pq->A[i].c)
            return i;
    return -1;
}

void fixDown(PQ pq, Item k, int **mindist){
    int j, i = getIndex(pq, k);
    if(LEFT(i) >= pq->heapsize || RIGHT(i) >= pq->heapsize)
        return;
    if(mindist[k.r][k.c] <= mindist[pq->A[LEFT(i)].r][pq->A[LEFT(i)].c] && mindist[k.r][k.c] <= mindist[pq->A[RIGHT(i)].r][pq->A[RIGHT(i)].c])
        return;
    if(mindist[pq->A[LEFT(i)].r][pq->A[LEFT(i)].c] >= mindist[pq->A[RIGHT(i)].r][pq->A[RIGHT(i)].c])
        j = RIGHT(i);
    else
        j = LEFT(i);
    swap(pq, i, j);
    fixDown(pq, k, mindist);
}

void fixUp(PQ pq, Item k, int **mindist){
  int i = getIndex(pq, k);
  if (pq->heapsize == 1 || i == 0)return;
  if (mindist[k.r][k.c] >= mindist[pq->A[PARENT(i)].r][pq->A[PARENT(i)].c])
    return;
  swap(pq, i, PARENT(i));
  fixUp(pq, k, mindist);
}

PQ PQinit(int maxN) {
  PQ x = malloc(sizeof(struct pqueue));
  x->A = malloc(maxN * sizeof(Item));
  x->heapsize = 0;
  return x;
}

int PQempty(PQ pq) {
  return pq->heapsize == 0;
}

void PQinsert(PQ pq, int **mindist, Item k) {
    int i = pq->heapsize++;
    pq->A[i] = k;
    fixUp(pq, k, mindist);
}

Item PQextractMin(PQ pq, int **mindist) {
  Item node = pq->A[0];
  swap(pq, 0, --pq->heapsize);
  fixDown(pq, pq->A[0], mindist);
  return node;
}

void PQchange(PQ pq, int **mindist, Item k){
  fixDown(pq, k, mindist);
  fixUp(pq, k, mindist);
}

void PQdisplay(PQ pq) {
    int i;
    for (i = 0; i < pq->heapsize; i++) {
        printf("<%2d, %2d> ", pq->A[i].r, pq->A[i].c);
    }
}