#include <stdio.h>

long fact(long n);

main() {
  long n;

  printf("Input n:  ");
  scanf("%d", &n);

  printf("factorial of %d is: %d \n", n, fact(n));
}

long fact(long n) {

  if(n == 0)
	return(1);
  return(n * fact(n-1));
}
