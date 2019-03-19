#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "PQ.h"
#define LEFT(i)   	((i*2) + 1)
#define RIGHT(i)	((i*2) + 2)
#define PARENT(i)	((i-1) / 2)

struct node { Item data; link l; link r; } ;

struct pqueue { link *array; int heapsize; };

link NEW(Item data, link l, link r) {
  link node = malloc(sizeof *node);
  node->data = data;
  node->l = l;
  node->r = r;
  return node;
}

PQ PQinit(int maxN){
  int i;
  PQ pq;
  pq = malloc(sizeof(*pq));
  pq->array = (link *)malloc(maxN*sizeof(link));
  for (i=0; i< maxN; i++)
    pq->array[i] = NEW(ITEMsetvoid(), NULL, NULL);
  pq->heapsize = 0;
  return pq;
}

int PQempty(PQ pq) {
  return pq->heapsize == 0;
}

int PQsize(PQ pq) {
  return pq->heapsize;
}

void PQinsert (PQ pq, link node) {
  int i;
  i  = pq->heapsize++;
  while( (i>=1) && (ITEMgreater(pq->array[PARENT(i)]->data, node->data)) ) {
    pq->array[i] = pq->array[PARENT(i)];
    i = (i-1)/2;
  }
  pq->array[i] = node;
  return;
}

void Swap(PQ pq, int n1, int n2) {
  link temp;
  temp  = pq->array[n1];
  pq->array[n1] = pq->array[n2];
  pq->array[n2] = temp;
  return;
}


void Heapify(PQ pq, int i) {
  int l, r, largest;
  l = LEFT(i);
  r = RIGHT(i);
  if ( (l < pq->heapsize) && (ITEMless(pq->array[l]->data, pq->array[i]->data)) )
    largest = l;
  else
    largest = i;
  if ( (r < pq->heapsize) && (ITEMless(pq->array[r]->data, pq->array[largest]->data)))
    largest = r;
  if (largest != i) {
    Swap(pq, i,largest);
	Heapify(pq, largest);
  }
  return;
}

link PQextractMin(PQ pq) {
  link node = malloc(sizeof(node));
  Swap (pq, 0,pq->heapsize-1);
  node = pq->array[pq->heapsize-1];
  pq->heapsize--;
  Heapify(pq, 0);
  return node;
}

Item NODEextract(link node) {
  return node->data;
}

void CODEdisplay(link n, char *code, int depth) {
  if (n->l==NULL && n->r==NULL) {
    code[depth] = '\0';
    printf("%s : %s\n", LETget(NODEextract(n)), code);
    return;
  }
  code[depth] = '0';
  CODEdisplay(n->l, code, depth+1);
  code[depth] = '1';
  CODEdisplay(n->r, code, depth+1);
}
