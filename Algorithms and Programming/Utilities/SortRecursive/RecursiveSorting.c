#include "Item.h"
#include "RecursiveSorting.h"
#define MAX 100

int min(int A, int B) {
   if (A < B)
      return A;
   else
      return B;
}

void Merge(Item *A, Item *B, int l, int q, int r) {
  int i, j, k;
  i = l;
  j = q+1;
  for(k = l; k <= r; k++)
    if (i > q)
      B[k] = A[j++];
    else if (j > r)
      B[k] = A[i++];
    else if ( less(A[i], A[j]) || eq(A[i], A[j])  )
      B[k] = A[i++];
    else
      B[k] = A[j++];
  for ( k = l; k <= r; k++ )
    A[k] = B[k];
  return;
}
/* versione di Merge con allocazione dinamica di B in ogni chiamata
se usata, ricordare di modificare anche main e Merge a proposito di B
Ricordare che per accedere correttamente agli elementi di B si usa come
indice k - l

void Merge(Item *A, int l, int q, int r) {
  int i, j, k, N;
  i = l;
  j = q+1;
  N = r - l + 1;
  Item *B;
  B = malloc(N*sizeof(Item));

  if (B == NULL) {
    printf("Memory allocation error\n");
    return;
  }

  for(k = l; k <= r; k++)
    if (i > q)
      B[k-l] = A[j++];
    else if (j > r)
      B[k-l] = A[i++];
    else if ( less(A[i], A[j]) || eq(A[i], A[j])  )
      B[k-l] = A[i++];
    else
      B[k-l] = A[j++];
  for ( k = l; k <= r; k++ )
    A[k] = B[k-l];
  return;
}
*/

void MergeSortR(Item *A, Item *B, int l, int r) {
  int q;
  if (r <= l)
    return;
  q = (l + r)/2;
  printf("l=%d r=%d\n", l, q);
  MergeSortR(A, B, l, q);
  printf("l=%d r=%d\n", q+1, r);
  MergeSortR(A, B, q+1, r);
  Merge(A, B, l, q, r);
}

void MergeSort(Item *A, int N) {
  int l=0, r=N-1;
  Item *B = (Item *)malloc(N*sizeof(Item));
  if (B == NULL) {
    printf("Memory allocation error\n");
    exit(1);
  }
  MergeSortR(A, B, l, r);
}

void BottomUpMergeSort(Item *A, int N) {
  int i, m, l=0, r=N-1;
  Item *B = (Item *)malloc(N*sizeof(Item));
  if (B == NULL) {
    printf("Memory allocation error\n");
    exit(1);
  }

  for (m = 1; m <= r - l; m = m + m) {
    for (i = l; i <= r-m ; i += m + m)
      Merge(A, B, i, i+m-1, min(i+m+m-1,r));
  }
  return;
}

void Swap( Item *v, int n1, int n2) {
  Item	temp;

  temp  = v[n1];
  v[n1] = v[n2];
  v[n2] = temp;
  return;
}


int partition ( Item *A, int l, int r ) {
  int i, j;
  Item x = A[r];
  i = l-1;
  j = r;
  for ( ; ; ) {
    while(less(A[++i], x));
    while(greater(A[--j], x))
    if (j == l)
      break;
    if (i >= j)
      break;
    Swap(A, i, j);
  }
  Swap(A, i, r);
  return i;
}

void QuickSortR( Item *A, int l, int r ) {
  int i, q;
  if (r <= l)
    return;
  q = partition(A, l, r);
  printf("risultato del partizionamento\n");
  for (i=l; i<=r; i++)
    ITEMshow(A[i]);
  printf("\n");
  QuickSortR(A, l, q-1);
  QuickSortR(A, q+1, r);
  return;
}

void QuickSort(Item *A, int N) {
  int l=0, r=N-1;
  QuickSortR(A, l, r);
}
