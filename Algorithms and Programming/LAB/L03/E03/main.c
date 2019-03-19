#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int i;
    int j;
} t_coord;

int main(int argc, char *argv[])
{
    char A[50][50];
    FILE *fp = NULL, *fp_c = NULL;
    int i,j,k=0,nr,nc,flag,dx,dy;
    t_coord m, reach;
    int semplice = 1, finito = 0;

    fp = fopen(argv[1], "r");
    fp_c = fopen(argv[2], "r");
    if(fp == NULL || fp_c == NULL)return -1;
    fscanf(fp, "%d %d", &nr, &nc);
    for(i=0; i<nr; i++)
        fscanf(fp, "%s", A[i]);
    fclose(fp);

    flag=0;
    for(i=0; i<nr && flag==0; i++)
        for(j=0; j<nc && flag==0; j++)
            if(A[i][j] == 'I')
                flag = 1;
    if(flag == 0){
        printf("Inizio non trovato");
        return 0;
    }

    i--;j--;

    A[i][j] = '+';
    while(fscanf(fp_c, "%d %d", &m.j, &m.i)!=EOF && !finito){
        if(m.i != 0 && m.j != 0){
            if(abs(m.i) != abs(m.j)){
                printf("Errore nella lettura dei passi");
                return 0;
            }
        }

        if(m.i == 0) dy=0;
        else if(m.i>0) dy=-1;
        else dy=1;

        if(m.j == 0) dx=0;
        else if(m.j>0) dx=1;
        else dx=-1;

        reach.i = i-m.i;
        reach.j = j+m.j;

        do{
            i += dy;
            j += dx;

            if(A[i][j] == '-' || A[i][j] == '+'){
                if(A[i][j] == '+')semplice = 0;
                else A[i][j] = '+';

            }else if(A[i][j] == 'U'){
                finito = 1;
            }else{
                printf("Passo in (%d,%d) non consentito", i+1, j+1);
                return 0;
            }
            k++;
        }while((i!=reach.i || j!=reach.j) && finito == 0);

    }
    if(finito == 0)
        printf("Non e' stata raggiunta la fine");
    else{
        if(semplice == 1)
            printf("Cammino semplice\n");
        else
            printf("Cammino non semplice\n");
        printf("Numero passi: %i\n", k);
    }
    fclose(fp_c);
    return 0;
}
