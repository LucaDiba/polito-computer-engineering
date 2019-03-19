#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(void) {
  int V, i, cont;

  printf("Input number of nodes: ");
  scanf("%d", &V);

  Graph G;
  G = GRAPHinit(V);

  cont = 1;
  while(cont) {
    printf("\nOperations on weighted undirected graphs\n");
    printf("===============\n");
    printf("1. Read graph from file\n");
    printf("2. Graph display\n");
    printf("3. MST with Kruskal's algorithm\n");
    printf("4.Exit\n");
    printf("Enter your choice : ");
    if(scanf("%d",&i)<=0) {
      printf("Integers only!\n");
      exit(0);
    }
    else {
      switch(i) {
              case 1:     GRAPHread(G);
                          break;
              case 2:     GRAPHshow(G);
                          break;
              case 3:     GRAPHmstK(G);
                          break;
              case 4:     cont = 0;
                          break;
              default:    printf("Invalid option\n");
          }
      }
  }
  return 0;
}
