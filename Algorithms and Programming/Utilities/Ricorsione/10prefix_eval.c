#include <stdio.h>
#include <string.h>
#include "Item.h"

static char *a;
static int i;

int eval();

main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Error: missing argument\n");
    printf("The correct format is:\n");
    printf("%s \"prefix expression with + and *\"\n", argv[0]);
    return 0;
  }

  a = argv[1];
  i = 0 ;
  printf("Result = %d", eval());
}

int eval() {
  int x = 0;

  while (a[i] == ' ')
    i++;

  if (a[i] == '+') {
    i++;
    return eval() + eval ();
  }
  if (a[i] == '*') {
    i++;
    return eval() * eval ();
  }

  while ((a[i] >= '0') && (a[i] <= '9'))
    x = 10 * x + (a[i++]-'0') ;

  return x;
}

