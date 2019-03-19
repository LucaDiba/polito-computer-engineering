#include <stdio.h>

long tr_2_iter_fact(long n, long f);

int main() {
  long  n;

  printf("Input n:  ");
  scanf("%ld", &n);

  printf("factorial of n is: %ld \n", tr_2_iter_fact(n, 1));
  return 0;
}

long tr_2_iter_fact(long  n, long f) {
  while (n > 0) {
    f = n * f;
    n--;
  }
  return f;
}
