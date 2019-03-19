#include <stdio.h>

#define N 8

int scacchiera[N][N];


int main ( )
{
  int i, j;
  
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      scacchiera[i][j] = 0;


  trova_powerset(0,0,0);    


}

int trova_powerset (int r, int c, int q)
{
  if (c>=N) {
    c=0; r++;
  }
  
  if (r>=N) { // scacchiera finita !
    if (q!=N) return 0;
	else if (controlla())
      return 1;
    else return 0;
  }

  // prova a mettere la regina su r,c
  scacchiera[r][c] = q+1;
  // ricorri
  if (trova_powerset (r,c+1,q+1))
    return 1;
 
  /* backtrack */
  scacchiera[r][c] = 0;
  // ricorri senza la regina su r,c
  if (trova_powerset (r,c+1,q))
    return 1;
  
  return 0;
}

int controlla (void) {
  int r, c, n;
  
  // controlla righe
  for (r=0; r<N; r++) {
    for (c=n=0; c<N; c++) {
      if (scacchiera[r][c]!=0) n++;
    }
	if (n>1) return 0;
  }
  // controlla colonne
  for (c=0; c<N; c++) {
    for (r=n=0; r<N; r++) {
      if (scacchiera[r][c]!=0) n++;
    }
	if (n>1) return 0;
  }
  // controlla diagonali: DA FARE !!!
  // ...
  
  return 1;
  
}
