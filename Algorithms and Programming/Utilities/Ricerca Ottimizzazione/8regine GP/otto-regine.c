/* costanti */
#define FAILURE 0
#define SUCCESS 1
#define EMPTY 0
#define FULL 1

#define N 8
#define ND (2*N-1)

/* prototipi */
int move(int, int *, char *, char *, char *);
void set(int, int, int *, char *, char *, char *);
void rem(int, int, int *, char *, char *, char *);

int main ( )
{
  int i, j;
  int queen[N];
  char row[N], dia[ND], revdia[ND];

  for (i=0; i<N; i++) 
    queen[i] = row[i] = EMPTY;
    
  for (i=0; i<ND; i++)
    dia[i] = revdia[i] = EMPTY;
  
  if (move(0, queen, row, dia, revdia) == SUCCESS) 
  {
    printf ("Risultato:\n");
    for(i=0; i<N; i++) 
      printf ("La regina %d si trova nella riga %d\n", i, queen[i]);
    printf ("\nRisultato in forma grafica\n");
    for(i=0; i<N; i++)
    { 
      for(j=0; j<N; j++) 
        if (queen[i]==j) 
          printf ("Q");
        else 
          printf ("*");
      printf ("\n");
    }   
  }
  return (SUCCESS);
}

int move(int n, int *queen, char *row, char *dia, char *revdia)
{
  int i;
  if (n == N) return (SUCCESS);
  for (i=0; i<N; i++) 
    if (row[i]==EMPTY && dia[n+i]==EMPTY && revdia[n-i+(N-1)]==EMPTY)     {
      set(n, i, queen, row, dia, revdia);
      if (move(n+1, queen, row, dia, revdia)) return (SUCCESS);
      rem(n, i, queen, row, dia, revdia);
    }
  return (FAILURE);
}

void set(int n, int i, int *queen, char *row, char *dia, char *revdia)
{
  queen[n] = i;
  row[i] = FULL;
  dia[n+i] = FULL;
  revdia[n-i+(N-1)] = FULL;
  return;
}

void rem(int n, int i, int *queen, char *row, char *dia, char *revdia)
{
  queen[n] = EMPTY;
  row[i] = EMPTY;
  dia[n+i] = EMPTY;
  revdia[n-i+(N-1)] = EMPTY;
  return;
}

