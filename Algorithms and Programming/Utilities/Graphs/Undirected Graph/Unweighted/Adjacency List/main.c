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
      printf("\nOperations on undirected unweighted graphs\n");
      printf("===============\n");
      printf("1.Read graph from file\n");
      printf("2.Edge insertion\n");
      printf("3.Edge removal\n");
      printf("4.Graph display\n");
      printf("5.Depth-first search\n");
      printf("6.Connected components\n");
      printf("7.Bridges\n");
      printf("8.Write graph on file\n");
      printf("9.Exit\n");
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
                case 3:     GRAPHremove(G);
                            break;
                case 4:     GRAPHshow(G);
                            break;
                case 5:     GRAPHdfs(G);
                            break;
                case 6:     printf("\nThe graph has %d connected component(s)\n", GRAPHcc(G));
                            break;
                case 7:     GRAPHbridge(G);
                            break;
                case 8:     GRAPHwrite(G);
                            break;
                case 9:     cont = 0;
                            break;
                default:    printf("Invalid option\n");
            }
        }
    }
    return 0;
}
