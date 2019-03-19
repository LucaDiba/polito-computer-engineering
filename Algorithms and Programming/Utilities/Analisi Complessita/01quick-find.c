#include <stdio.h>
#define N 11
main() {
  int i, t, p, q, id[N];

  for(i=0; i<N; i++)
    id[i] = i;

  printf("Input pair p q:  ");
  while (scanf("%d %d", &p, &q) ==2) {
    if (id[p] == id[q])
	  printf("pair %d %d already connected\n", p,q);
	else {
      for (t = id[p], i = 0; i < N; i++)
        if (id[i] == t)
          id[i] = id[q];
      printf("pair %d %d not yet connected\n", p, q);
    }
    printf("Now array id contains:\n");
    for(i=0; i<N; i++)
      printf("%d ", id[i]);
    printf("\n\n");

    printf("Input pair p q:  ");
  }
}
