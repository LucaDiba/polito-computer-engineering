#include <stdio.h>
#include <stdlib.h>
#include "Dag.h"

int main(void) {
  int V, i, cont;

  printf("Input number of nodes: ");
  scanf("%d", &V);

  Dag D;
  D = DAGinit(V);

    cont = 1;
    while(cont) {
      printf("\nOperations on unweighted directed graphs\n");
      printf("===============\n");
      printf("1.Read graph from file\n");
      printf("2.Edge insertion\n");
      printf("3.Edge removal\n");
      printf("4.Graph display\n");
      printf("5.Reverse topological sort\n");
      printf("6.Exit\n");
      printf("Enter your choice : ");
      if(scanf("%d",&i)<=0) {
        printf("Integers only!\n");
        exit(0);
      }
      else {
        switch(i) {
                case 1:     DAGread(D);
                            break;
                case 2:     DAGinsert(D);
                            break;
                case 3:     DAGremove(D);
                            break;
                case 4:     DAGshow(D);
                            break;
                case 5:     DAGrts(D);
                            break;
                case 6:     cont = 0;
                            break;
                default:    printf("Invalid option\n");
            }
        }
    }
    return 0;
}
