#include <stdio.h>
#define MAX 8
#include <math.h>

//long product(int *x, int *y, int n);
long product(int *x, int lx, int rx, int *y, int ly, int ry, int n);

void main(void) {
  int i, n;
  int a[MAX], b[MAX];

  printf("input n = 2^k: ");
  scanf("%d", &n);

  printf("input first term: \n");
  for(i=0; i<n; i++) {
    printf("a[%d] = ", i);
    scanf("%d", &a[i]);
  }

  printf("input second term: \n");
  for(i=0; i<n; i++) {
    printf("b[%d] = ", i);
    scanf("%d", &b[i]);
  }
  printf("The result is: %ld\n", product(a, 0, n-1, b, 0, n-1, n));
}


long product(int *x, int lx, int rx, int *y, int ly, int ry, int n) {
  int  i,term1,term2, term3;
  if(n > 1) {
    term1 = product(x, lx, (lx+rx)/2, y, ly, (ly+ry)/2, n/2);
    term2 = product(x, lx, (lx+rx)/2, y, ly+n/2, ry, n/2) + product(x, lx+n/2, rx, y, ly, (ly+ry)/2, n/2);
    term3 = product(x, lx+n/2, rx, y, ly + n/2, ry, n/2);
    return term1 * pow(10,n) + term2 * pow (10, n/2) + term3;
    }
  else
    return (x[lx]*y[ly]);
}
