#include <stdio.h>

long fib(long n);

main() {
  long n;

  printf("Input n:  ");
  scanf("%d", &n);

  printf("fibonacci of %d is: %d \n", n, fib(n));
}

long fib(long n) {
  if(n == 0 || n == 1)
    return(n);

  return(fib(n-2) + fib(n-1));
}

