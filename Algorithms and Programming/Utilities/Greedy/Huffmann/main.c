#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"
#include "PQ.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Error: missing argument\n");
    printf("correct format:\n");
    printf("%s maxN \n", argv[0]);
    return 0;
  }
  int i, maxN = atoi(argv[1]);
  link node, nodeL, nodeR, root;
  Item item;
  char code[maxN+1];

  PQ pq = PQinit(maxN);

  for (i=0; i<maxN; i++) {
    node = NEW(ITEMscan(), NULL, NULL);
    PQinsert(pq, node);
  }

  while (PQsize(pq) > 1) {
    nodeL = PQextractMin(pq);
    nodeR = PQextractMin(pq);
    item = ITEMnew(NODEextract(nodeL), NODEextract(nodeR));
    node = NEW(item, nodeL, nodeR);
    PQinsert(pq, node);
  }
  root = PQextractMin(pq);

  printf("\nHuffman code is:\n");
  CODEdisplay(root, code, 0);

  return 1;
}


