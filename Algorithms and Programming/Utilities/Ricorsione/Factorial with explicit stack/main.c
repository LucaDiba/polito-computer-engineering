#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#define N 100

long fact(long n);

int main(void)
{
	long n;
	printf("Input n:  ");
    scanf("%ld", &n);
    printf("factorial of %ld is: %ld \n", n, fact(n));
    return 0;
}

long fact (long n){
  long f = 1;
  S stack;
  stack = STACKinit(N);

  while (n>0) {
    STACKpush(stack, n);
    n--;
  }

  while (STACKsize(stack) > 0) {
    n = STACKpop (stack);
    f = n * f;
  }
  return f;
}
