#include <stdio.h>
#include <stdlib.h>



void SP_rec(int n, int k, int m, int p, int *sol, int *val);
void SetPartitions(int n, int k, int *sol, int *val);

int main(void){
  int i, n, k, *val, *sol;

  printf("\n");
  printf("\nCalcolo delle partizioni di un insiemi di n elementi in k blocchi\n");
  printf("Inserisci il numero n di elementi: ");
  scanf("%d", &n);
  printf("Inserisci il numero k di blocchi: ");
  scanf("%d", &k);

  val = malloc(n * sizeof(int));
  sol = malloc(n * sizeof(int));

  for(i=0; i<n; i++)
    sol[i] = 0;

  for (i=0; i<n; i++) {
    printf("Inserisci elementi: ");
    scanf("%d", &val[i]);
  }

  printf("Le partizioni di %d elementi in %d blocchi sono \n", n, k);

  SetPartitions(n, k, sol, val);

  free(val);
  free(sol);

  return 0;
}

void SetPartitions(int n, int k, int *sol, int *val) {
  SP_rec(n, k, 0, 0, sol, val);
  return;
}

void SP_rec(int n, int k, int m, int pos, int *sol, int *val) {
  int i, j;
  if (pos >= n) {
    if (m == k) {
      for (i=0; i<m; i++) {
        printf("{ ");
        for (j=0; j<n; j++) {
          if (sol[j]==i)
            printf("%d ", val[j]);
        }
        printf("}  ");
     }
      printf("\n");
    }
    return;
  }

  for (i=0; i<m; i++) {
    sol[pos] = i;
    SP_rec(n, k, m, pos+1, sol, val);
  }
  sol[pos] = m;
  SP_rec(n, k, m+1, pos+1, sol, val);
}

