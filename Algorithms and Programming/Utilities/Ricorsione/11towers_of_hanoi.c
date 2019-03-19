#include <stdio.h>

void Hanoi(int n, int src, int dest);

main() {
  int n, src, dest;

  printf("Towers of Hanoi\n");
  printf("insert number of disks: \n");
  scanf("%d" , &n);
  printf("insert source  peg (0/1/2): \n");
  scanf("%d" , &src);
  printf("insert destination peg (0/1/2): \n");
  scanf("%d" , &dest);

  Hanoi(n , src, dest );
}


void Hanoi(int n, int src, int dest) {
  int aux;

  aux = 3 - (src + dest);

  if (n == 1) {
    printf("src %d -> dest %d \n", src, dest);
    return;
  }

  Hanoi(n-1, src, aux);

  printf("src %d -> dest %d \n", src, dest);

  Hanoi(n-1, aux, dest);
}

