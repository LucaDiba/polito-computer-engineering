#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "Heap.h"

struct heap { Item *A; int heapsize; };

int LEFT(int i) {
  return i*2+1;
}

int RIGHT(int i) {
  return i*2+2;
}

int PARENT(int i) {
  return (i-1)/2;
}

Heap HEAPinit(int maxN) {
  Heap h;
  h = malloc(sizeof(*h));
  h->A = malloc(maxN*sizeof(Item));
  h->heapsize = 0;
  return h;
}

void HEAPfill(Heap h, Item item) {
  int i;
  i  = h->heapsize++;
  h->A[i] = item;
}

void Swap(Heap h, int n1, int n2) {
  Item tmp;
  tmp  = h->A[n1];
  h->A[n1] = h->A[n2];
  h->A[n2] = tmp;
}

void HEAPify(Heap h, int i) {
  int l, r, largest;
  l = LEFT(i);
  r = RIGHT(i);
  if (l < h->heapsize && ITEMgreater(h->A[l], h->A[i]))
    largest = l;
  else
    largest = i;
  if (r < h->heapsize && ITEMgreater(h->A[r], h->A[largest]))
    largest = r;
  if (largest != i) {
    Swap(h, i,largest);
	HEAPify(h, largest);
  }
}

void HEAPbuild (Heap h) {
  int i;
  for (i=(h->heapsize)/2-1; i >= 0; i--)
    HEAPify(h,i);
}

void HEAPsort(Heap h) {
  int i,j;
  HEAPbuild(h);
  printf("The heap before sorting is:\n");
  HEAPdisplay(h);
  j = h->heapsize;
  for (i = h->heapsize-1; i > 0; i--) {
    Swap (h,0,i);
    h->heapsize--;
	HEAPify(h,0);
    printf("---> Passo %d\n", i);
    HEAPdisplay(h);
  }
  h->heapsize = j;
}

void HEAPdisplay(Heap h) {
  int i;
  for (i = 0; i < h->heapsize; i++)
    ITEMshow(h->A[i]);
}