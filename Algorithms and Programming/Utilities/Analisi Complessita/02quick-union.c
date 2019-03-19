#include <stdio.h>
#define N 11
main() {
  int i, j, p, q, id[N];

  for(i=0; i<N; i++)
    id[i] = i;

  printf("Input pair p q:  ");
  while (scanf("%d %d", &p, &q) ==2) {
    for (i = p; i!= id[i]; i = id[i]);
	for (j = q; j!= id[j]; j = id[j]);
	if (i == j)
      printf("pair %d %d already connected\n", p,q);
	else {
      id[i] = j;
      printf("pair %d %d not yet connected\n", p, q);
    }
    printf("Now array id contains:\n");
    for(i=0; i<N; i++)
      printf("%d ", id[i]);
    printf("\n\n");
    printf("Input pair p q:  ");
  }
}
