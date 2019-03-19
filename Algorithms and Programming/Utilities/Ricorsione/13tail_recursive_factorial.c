#include <stdio.h>

long tr_fact(long n, long f);

int main() {
  long  n;

  printf("Input n:  ");
  scanf("%ld", &n);

  printf("factorial of n is: %ld \n", tr_fact(n, 1));
  return 0;
}

long tr_fact(long  n, long f) {
  if(n == 0)
    return(f);
  return tr_fact(n-1, n*f);
}
