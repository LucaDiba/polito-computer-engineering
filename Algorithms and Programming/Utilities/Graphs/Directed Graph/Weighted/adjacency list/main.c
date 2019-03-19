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
      printf("\nOperations on unweighted directed graphs\n");
      printf("===============\n");
      printf("1.Read graph from file\n");
      printf("2.Edge insertion\n");
      printf("3.Graph display\n");
      printf("4.Shortest path with Dijksta's algorithm\n");
      printf("5.Shortest path with Bellman-Ford's algorithm\n");
      printf("6.Exit\n");
      printf("Enter your choice : ");
      if(scanf("%d",&i)<=0) {
        printf("Integers only!\n");
        exit(0);
      }
      else {
        switch(i) {
                case 1:     GRAPHread(G);
                            break;
                case 2:     GRAPHinsert(G);
                            break;
                case 3:     GRAPHshow(G);
                            break;
                case 4:     GRAPHspD(G);
                            break;
                case 5:     GRAPHspBF(G);
                            break;
                case 6:     cont = 0;
                            break;
                default:    printf("Invalid option\n");
            }
        }
    }
    return 0;
}
