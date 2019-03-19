int main() {

  int i, k, cap;
  Item *items;

  printf("Input number of elements: ");
  scanf("%d", &k);

  items = malloc(k*sizeof(Item));

  printf("Input capacity of knapsack: ");
  scanf("%d", &cap);

  printf("Input elements: \n");
  for (i=0; i<k; i++)
    items[i] = ITEMscan();

  return 0;
}

int subseq(char *X, char *Y) {
  while (*X != '\0') {
    if (*Y == *X) {
      Y++;
      if (*Y == '\0')
        return 1;
    }
    X++;
  }
  return 0;
}

int LCSlengthDP(char *X, char *Y) {
  int i, j, m, n, **c;
//  int i, j, m, n, **c, **b;
  m = strlen(X);
  n = strlen(Y);

  c = calloc((m+1), sizeof(int));
//  b = calloc((m+1), sizeof(int));

  for (i = 0; i <= m; i++) {
    c[i] = calloc((n+1), sizeof(int));
//    b[i] = calloc((n+1), sizeof(int));
  }

  for (i=1; i<=m; i++)
    for (j=1; j <=n; j++)
      if (X[i-1]==Y[j-1]) {
        c[i][j] = c[i-1][j-1]+1;
//        b[i][j] = 1;
      }
      else {
        if (c[i-1][j] >= c[i][j-1]) {
          c[i][j] = c[i-1][j];
//          b[i][j] = 2;
        }
        else {
          c[i][j] = c[i][j-1];
//          b[i][j] = 3;
        }
      }

  printf("c is: \n");
  for (i=0; i<=m; i++) {
    for (j=0; j <=n; j++)
      printf("%d ", c[i][j]);
    printf("\n");
  }
/*
  printf("b is: \n");
  for (i=0; i<=m; i++) {
    for (j=0; j <=n; j++)
      printf("%d ", b[i][j]);
    printf("\n");
  }
*/

  printf("LCS is: ");
//  displaySol(X, Y, b);
  displaySol(X, Y, c);
  printf("\n");
  return c[m][n];
}

void displaySolR(char *X, char *Y, int **c, int i, int j) {
  if ((i==0) || (j==0)) {
    return;
  }
  if (X[i-1]==Y[j-1]) {
    displaySolR(X, Y, c, i-1, j-1);
    printf("%c", X[i-1]);
    return;
  }
  if (c[i-1][j] >= c[i][j-1])
    displaySolR(X, Y, c, i-1, j);
  else
    displaySolR(X, Y, c, i, j-1);
}

void displaySol(char *X, char *Y, int **c) {
  int m, n;
  m = strlen(X);
  n = strlen(Y);
  displaySolR(X, Y, c, m, n);
}

/*
void displaySolR(char *X, char *Y, int **b, int i, int j) {
  if ((i==0) || (j==0)) {
    return;
  }
  if (b[i][j]==1) {
    displaySolR(X, Y, b, i-1, j-1);
    printf("%c", X[i-1]);
    return;
  }
  if (b[i][j]==2)
    displaySolR(X, Y, b, i-1, j);
  else
    displaySolR(X, Y, b, i, j-1);
}

void displaySol(char *X, char *Y, int **b) {
  int m, n;
  m = strlen(X);
  n = strlen(Y);
  displaySolR(X, Y, b, m, n);
}
*/

int max(int a, int b) {
  if (a >= b)
    return a;
  return b;
}

int maxValR(int *value, int *weight, int i, int j) {
  if ( (i == 0) || (j == 0))
    return 0;
  if (weight[i] >j)
    return maxValR(value, weight, i-1, j);
  else
    return max(maxValR(value, weight, i-1, j), maxValR(value, weight, i-1, j-weight[i])+value[i]);
}

int KNAPval(int *value, int *weight, int n, int cap) {
  return maxValR(value, weight, n, cap);
}

/*

int lcs_length(char *s1, char *s2) {
  if (*s1 == '\0' || *s2 == '\0')
    return 0;
  if (*s1 == *s2)
    return 1 + lcs_length(s1+1, s2+1);
  else
    return max(lcs_length(s1+1, s2), lcs_length(s1, s2+1));
}
*/

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

void powerset(int pos, Item *items, int *sol, int k, int cap, int curr_cap, int curr_value, int *bv, int *best_sol);

int main(void)
{
    int i, k, cap, *sol, *best_sol, best_value=0;
    Item *items;

    printf("Input number of elements: ");
    scanf("%d", &k);

    items = malloc(k*sizeof(Item));
    sol = malloc(k*sizeof(int));
    best_sol = malloc(k*sizeof(int));

    for (i=0; i<k; i++)
    {
        sol[i] = 0;
        best_sol[i] = 0;
    }

    printf("Input capacity of knapsack: ");
    scanf("%d", &cap);

    printf("Input elements: \n");
    for (i=0; i<k; i++)
        items[i] = ITEMscan();


    powerset(0, items, sol, k, cap, 0, 0, &best_value, best_sol);

    printf("The solution is set { ");
    for (i=0; i<k; i++)
        if (best_sol[i]!=0)
            ITEMshow(items[i]);
    printf("} \n");
    printf("best value = %d \n", best_value);

    return 1;

}

void powerset(int pos, Item *items, int *sol, int k, int cap, int curr_cap, int curr_value, int *bv, int *best_sol)
{
    int j;

    if (pos >= k)
    {
        if (curr_cap <= cap)
        {
            if (curr_value > *bv)
            {
                for (j=0; j<k; j++)
                    best_sol[j] = sol[j];
                *bv = curr_value;
            }
        }
        return;
    }
    sol[pos] = 1;
    curr_cap += items[pos].size;
    curr_value += items[pos].value;
    powerset(pos+1, items, sol, k, cap, curr_cap, curr_value, bv, best_sol);
    sol[pos] = 0;
    curr_cap -= items[pos].size;
    curr_value -= items[pos].value;
    powerset(pos+1, items, sol, k, cap, curr_cap, curr_value, bv, best_sol);
}



