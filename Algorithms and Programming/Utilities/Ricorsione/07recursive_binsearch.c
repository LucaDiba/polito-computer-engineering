#include <stdio.h>
#include <stdlib.h>

#define V 8

int BinSearch(int v[], int l, int r, int k);

main() {
  int i, k, a[V];

  for (i=0; i<V; i++) {
    printf("Input a[%d]:", i);
    scanf("%d", &a[i]);
  }

  printf("Input key:  ");
  scanf("%d", &k);

  printf("if output -1 key not found, else found at index: %d\n", BinSearch(a, 0, i-1, k));
}
/*
int BinSearch(int v[], int l, int r, int k) {
   int m;

   if (l > r)
      return -1;

   m = (l + r) / 2;


   if (k < v[m])
      return BinSearch(v, l, m-1, k);
   if (k > v[m])
      return BinSearch(v, m+1, r, k);
   return (m);
}
*/

int BinSearch(int v[], int l, int r, int k) {
  int m;
  if (l > r)
    return -1;

  m = (l + r) / 2;

  if (k == v[m])
    return (m);

  if (k < v[m])
    return BinSearch(v, l, m-1, k);

  return BinSearch(v, m+1, r, k);
}
