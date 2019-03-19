#include <stdio.h>

int gcd(int x, int y);

main() {
  int x, y;
  printf("Input x and y:  ");
  scanf("%d%d", &x, &y);

  printf("gcd of %d and %d is: %d \n", x, y, gcd(x, y));
}


int gcd(int x, int y) {
  if(x == y)
    return(x);
  if (x > y)
    return gcd(x-y, y);
  else
    return gcd(x, y-x);
}

/*
int gcd(int x, int y) {
  if(y == 0)
    return(x);
  return gcd(y, x % y);
}
*/
