#include <stdio.h>

long fib(long n);

main() {
  long n;

  printf("Input n:  ");
  scanf("%d", &n);

  printf("fibonacci of n is: %d \n", fib(n));
}

long fib(long n) {
  long f1p=1, f2p=0, f;
  int i;

  if(n == 0 || n == 1)
    return(n);

  f = f1p + f2p; /* n==2 */

  for(i=3; i<= n; i++) {
    f2p = f1p;
    f1p = f;
    f = f1p+f2p;
  }
  return(f);
}

