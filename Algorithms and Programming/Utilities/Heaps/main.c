#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "Heap.h"

int main(int argc, char *argv[]) {
if (argc !=4) {
  printf("Error in command line, correct format: \n");
  printf("main <array size> <# of items> <1 for random input, 0 for input from keyboard>\n");
  exit(1);
  }

  int i=0,  maxN = atoi(argv[1]), N = atoi(argv[2]), sw = atoi(argv[3]);
  Item item;
  Heap a = HEAPinit(maxN);

  if (sw) {
    printf("Filling in the array with random items\n");
    for (i = 0; i < N; i++)
      HEAPfill(a, ITEMrand());
    }
  else {
    printf("Input items, max %d\n", N);
    for (i = 0; i < N; i++) {
      item = ITEMscan();
      HEAPfill(a, item);
    }
  }
  HEAPsort(a);

  printf("Array a sorted in ascending order is:\n");
  HEAPdisplay(a);
  return 0;
}


