#include <stdio.h>

#define N 8

int scacchiera[N][N];

int main ( )
{
  int i, j;
  
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      scacchiera[i][j] = 0;

  trova(0,0,0);    


}

int trova (int r0, int c0, int q)
{
  int r, c;
  if (q==N) {
    if (controlla())
      return 1;
    else return 0;
  }

  for (r=r0; r<N; r++) 
    for (c=0; c<N; c++) {
      if (((r>r0) || ((r==r0)&&(c>c0))) && scacchiera[r][c] == 0) {
        scacchiera[r][c] = 1;
        if (trova (r,c,q+1)) {
          return 1;
        }
        /* backtrack */
        scacchiera[r][c] = 0;
      }
  }
  return 0;
}

