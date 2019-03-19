#include <stdio.h>
#include <stdlib.h>


int powerset_disp_rep(int pos, int *val, int *sol, int k, int count);
int powerset_div_conq(int pos, int *val, int *sol, int k, int start, int count);
int powerset_simp_comb(int* val, int k, int* sol);

int main(void) {
  int i, k, cnt, *val, *sol;

  printf("Input number of elements: ");
  scanf("%d", &k);

  val = malloc(k*sizeof(int));
  sol = malloc(k*sizeof(int));

  for (i=0; i<k; i++)
    sol[i] = 0;

  printf("Input elements: \n");
  for (i=0; i<k; i++) {
    printf("val[%d] = ", i);
    scanf("%d", &val[i]);
  }

  printf("The powerset of set {");
  for(i =0; i<k; i++)
    printf(" %d ", val[i]);
  printf(" } is \n");

  printf("arrangements with repetitions\n");
  cnt = powerset_disp_rep(0, val, sol, k, 0);
  printf ("number of sets: %d \n", cnt);

  printf("divide and conquer\n");
  cnt = powerset_div_conq(0, val, sol, k, 0, 0);
  printf ("number of sets: %d \n", cnt);

  printf("simple combinations\n");
  cnt = powerset_simp_comb(val, k, sol);
  printf ("number of sets: %d \n", cnt);

  free(val);
  free(sol);

  return;
}

int powerset_disp_rep(int pos, int *val, int *sol, int k, int count) {
  int j;

  if (pos >= k) {
    printf("{ ");
    for (j=0; j<k; j++)
      if (sol[j]!=0)
        printf("%d ", val[j]);
      printf("} \n");
      return count+1;
  }

  sol[pos] = 0;
  count = powerset_disp_rep(pos+1, val, sol, k, count);
  sol[pos] = 1;
  count = powerset_disp_rep(pos+1, val, sol, k, count);
  return count;
}

int powerset_div_conq(int pos, int *val, int *sol, int k, int start, int count) {
   int i;
   if (start >= k) {
      printf("{ ");
       for (i = 0; i < pos; i++)
         printf("%d ", sol[i]);
      printf("} \n");
      return count+1;
   }
   for (i = start; i < k; i++) {
      sol[pos] = val[i];
      count = powerset_div_conq(pos+1, val, sol, k, i+1, count);
   }
   count = powerset_div_conq(pos, val, sol, k, k, count);
   return count;
}

int powerset_simp_comb(int* val, int k, int* sol){
   int count = 0, n;
   printf("{ }\n");
   count++;
   for(n = 1; n <= k; n++){
      count += powerset_r(val, k, sol, n, 0, 0);
   }
   return count;
}

int powerset_r(int* val, int k, int* sol, int n,
               int pos, int start){
   int count = 0, i;
   if (pos == n){
      printf("{ ");
      for (i = 0; i < n; i++)
         printf("%d ", sol[i]);
      printf("}\n");
      return 1;
   }
   for (i = start; i < k; i++){
      sol[pos] = val[i];
      count += powerset_r(val, k, sol, n, pos+1, i+1);
   }
   return count;
}
