#include <stdio.h>

#define N 8

int scacchiera[N][N];

int main ( )
{
  int i, j;
  
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      scacchiera[i][j] = 0;

  trova(0);    

}

int trova (int q)
{
  int r, c;
  if (q==8) {
    if (controlla())
      return 1;
    else return 0;
  }

  for (r=0; r<N; r++) 
    for (c=0; c<N; c++) {
      if (scacchiera[r][c] == 0) {
        scacchiera[r][c] = q+1;
        if (trova (q+1)) {
          return 1;
        }
        /* backtrack */
        scacchiera[r][c] = 0;
      }
  }
  return 0;
}

