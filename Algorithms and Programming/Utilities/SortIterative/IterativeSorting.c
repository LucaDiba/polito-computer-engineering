#include "Item.h"
#include "IterativeSorting.h"

void BubbleSort(Item *A, int l, int r) {
  int i, j;
  Item temp;

  for(i = l; i < r; i++) {
    for (j = l; j <  r - i + l; j++) {
	  printf("i = %d j=%d\n", i, j);
	  if (greater(A[j], A[j+1])) {
        temp = A[j];
        A[j] = A[j+1];
		A[j+1] = temp;
      }
    }
  }

  return;
}

void OptBubbleSort(Item *A, int l, int r) {
  int i, j, flag;
  Item temp;

  flag = 1;
  for(i = l; i < r && flag == 1; i++) {
    flag = 0;
    for (j = l; j < r - i + l; j++)
      if (greater(A[j],A[j+1])) {
        flag = 1;
        temp = A[j];
        A[j] = A[j+1];
		A[j+1] = temp;
      }
  }
  return;
}

void SelectionSort(Item *A, int l, int r) {
  int i, j, min;
  Item temp;
  for(i = l; i < r; i++) {
    min = i;
	for (j = i + 1; j <= r; j++)
      if (less(A[j],A[min]))
        min = j;
      temp = A[i];
      A[i] = A[min];
      A[min] = temp;
  }
  return;
}

void InsertionSort(Item *A, int l, int r) {
  int i, j;
  Item x;
  for(i = l+1; i <= r; i++) {
    x = A[i];
    j = i - 1;
    while (j >= l && less(x, A[j])) {
      A[j+1] = A[j];
      j--;
    }
    A[j+1] = x;
  }
}

void ShellSort(Item *A, int l, int r) {
  int i, j, h=1, n = r-l+1;
  Item tmp;

  while (h < n/3)
    h = 3*h+1;
  while(h >= 1) {
    for (i = l + h; i <= r; i++) {
      j = i;
      tmp = A[i];
      while(j >= l + h  && less(tmp,  A[j-h])) {
        A[j] = A[j-h];
        j -=h;
      }
      A[j] = tmp;
    }
    printf("h = %d, h-sorted array is: \n", h);
    for (i = 0; i <(r-l+1); i++)
      ITEMshow(A[i]);
    printf("\n");
    h = h/3;
  }
}

void CountingSort(Item *A, int l, int r, int k) {
  int i, n, *C;
  Item *B;

  n = r - l + 1;
  B  = (Item *)malloc(n*sizeof(Item));
  C  = (int *)malloc(k*sizeof(int));

  for (i = 0; i < k; i++)
    C[i] = 0;

  for (i = l; i <= r; i++)
    C[key(A[i])]++;

  for (i = 1; i < k; i++)
    C[i] += C[i-1];

  for (i = r; i >= l; i--) {
    B[C[key(A[i])]-1] = A[i];
    C[key(A[i])]--;
  }

  for (i = l; i <= r; i++)
    A[i] = B[i];
}

