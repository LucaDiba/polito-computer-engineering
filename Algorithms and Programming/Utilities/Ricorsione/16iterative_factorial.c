#include <stdio.h>

long fact(long n);

main() {
  long  n;

  printf("Input n:  ");
  scanf("%d", &n);

  printf("factorial of n is: %d \n", fact(n));
}

long fact(long  n) {
  long tot = 1;
  int i;

  for(i=2; i<=n; i++)
	tot = tot * i;

  return(tot);
}
