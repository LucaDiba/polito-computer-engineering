#include <stdio.h>
#include <math.h>

void ruler(int l, int r, int h);
void mark(int m, int h);

void main() {
  int n, x;

  printf("input max height n: ");
  scanf("%d", &n);

  printf("horizontally print a ruler with 2^%d + 1 marks \n", n);

  printf("0 \t \n");
  ruler(0, pow(2,n), n);
  x= pow(2,n);
  printf("%d \t \n", x);
}


void ruler(int l, int r, int h) {
  int m;

  m = (l + r)/2;

  if (h > 0) {
    ruler(l, m, h-1);
    mark(m, h);
    ruler(m, r, h-1);
  }
}

void mark(int m, int h) {
  int i;

  printf("%d \t", m);
  for (i = 0; i < h; i++)
    printf("*");
  printf("\n");
}
