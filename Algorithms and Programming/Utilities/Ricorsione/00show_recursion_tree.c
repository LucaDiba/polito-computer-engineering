#include <stdio.h>
#define MAX 32
#include <math.h>


void show(int x[], int l, int r);
//void show1(int x[], int l, int r);
void show2(int x[], int l, int r);

void main(void) {
  int i, n;
  int a[MAX];

  printf("input n = 2^k: ");
  scanf("%d", &n);

  printf("input  array \n");
  for(i=0; i<n; i++) {
    printf("a[%d] = ", i);
    scanf("%d", &a[i]);
  }

  printf("x = ");
  for(i=0; i<n; i++)
    printf("%d", a[i]);
  printf("\n");

  show(a, 0, n-1);

}

void show(int x[], int l, int r) {
  int i, c;

  if(l >= r)
    return;

  c = (r+l)/2;

  printf("xs = ");
  for (i=l; i <= c; i++)
    printf("%d", x[i]);
  printf("\n");
  show(x, l, c);

  printf("xd = ");
  for (i=c+1; i <= r; i++)
    printf("%d", x[i]);
  printf("\n");
  show(x, c+1, r);

  return;
}
