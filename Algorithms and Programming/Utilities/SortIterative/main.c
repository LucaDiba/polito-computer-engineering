#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Item.h"
#include "IterativeSorting.h"


int main(int argc, char *argv[]) {

  if (argc !=3) {
    printf("Error in command line, correct format: \n");
    printf("client <number of keys> <1 for random input, 0 for for input from keyboard\n");
    exit(1);
  }

  int i=0, max = 0, k, N = atoi(argv[1]), sw = atoi(argv[2]);
  Item *a = (Item *)malloc(N*sizeof(Item));
  if (a == NULL) {
    printf("Memory allocation error\n");
    return EXIT_FAILURE;
  }

  if (sw) {
    printf("Filling in the array with random values\n");
    srand(time(NULL));
    for (i = 0; i < N; i++)
      a[i] = ITEMrand();
  }
  else {
    printf("Input array values (key is >=0) \n");
    for (i = 0; i < N; i++) {
      a[i] = ITEMscan();
      if (key(a[i]) > max)
        max = key(a[i]);
    }
    k = max +1;
    printf("\n");
  }
  printf("The original array is\n");
  for (i = 0; i <N; i++) {
    printf("a[%d]: ", i);
    ITEMshow(a[i]);
  }
  printf("\n");

  printf("\nIterative Sorting Algorithms\n");
  printf("===============\n");
  printf("1. Bubble sort\n");
  printf("2. Optimized bubble sort\n");
  printf("3. Selection sort\n");
  printf("4. Insertion sort\n");
  printf("5. Shell sort\n");
  printf("6. Counting sort\n");
  printf("7. Exit\n");
  printf("Enter your choice : ");
  if(scanf("%d",&i)<=0) {
    printf("Integers only!\n");
    exit(0);
  }
  else {
    switch(i) {
      case 1:     BubbleSort(a, 0, N-1);
                  break;
      case 2:     OptBubbleSort(a, 0, N-1);
                  break;
      case 3:     SelectionSort(a, 0, N-1);
                  break;
      case 4:     InsertionSort(a, 0, N-1);
                  break;
      case 5:     ShellSort(a, 0, N-1);
                  break;
      case 6:     CountingSort(a, 0, N-1, k);
                  break;
      case 7:     break;
      default:    printf("Invalid option\n");
    }
  }
  printf("Array a sorted in ascending order for key x is:\n");
  for (i = 0; i <N; i++) {
    printf("a[%d]: ", i);
    ITEMshow(a[i]);
  }
  printf("\n");
  return 0;
}
