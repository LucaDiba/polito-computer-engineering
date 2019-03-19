#include <stdio.h>
#include <stdlib.h>
#define NR 20
#define NC 20

int Somma(int M[NR][NC], int i_start, int i_end, int j_start, int j_end);
void ScansionaMatrice(FILE *fp, int M[NR][NC], int nr, int nc);
void StampaMatrice(int M[NR][NC], int nr, int nc);

int main()
{
    FILE *fp = NULL;
    int i, j, nr, nc, M[NR][NC], ins_i, ins_j, somma;

    fp = fopen("matrice.txt", "r");
    if(fp == NULL)return -1;
    fscanf(fp, "%i %i%*c", &nr, &nc);
    ScansionaMatrice(fp, M, nr, nc);
    StampaMatrice(M, nr, nc);
    printf("\n");
    while(printf("Inserisci i j: ") > 0 && scanf("%i %i%*c", &ins_i, &ins_j) == 2 &&
          ins_i >= 0 && ins_i < nr && ins_j >= 0 && ins_j < nc){
        // NO
        printf("NO = ");
        somma = Somma(M, 0, ins_i-1, 0, ins_j-1);
        printf(" = %i\n", somma);
        // NE
        printf("NE = ");
        somma = Somma(M, 0, ins_i-1, ins_j+1, nc-1);
        printf(" = %i\n", somma);
        // SO
        printf("SO = ");
        somma = Somma(M, ins_i+1, nr-1, 0, ins_j-1);
        printf(" = %i\n", somma);
        // SE
        printf("SE = ");
        somma = Somma(M, ins_i+1, nr-1, ins_j+1, nc-1);
        printf(" = %i\n", somma);

        printf("\n");
    }

    fclose(fp);
    return 0;
}

int Somma(int M[NR][NC], int i_start, int i_end, int j_start, int j_end){
    int somma = 0,i,j,tmp;
    for(i=i_start; i<=i_end; i++)
        for(j=j_start; j<=j_end; j++){
            tmp = M[i][j];
            printf("%i", tmp);
            somma += tmp;
            if(i != i_end || j != j_end)
                printf(" + ");
        }
    return somma;
}

void ScansionaMatrice(FILE *fp, int M[NR][NC], int nr, int nc){
    int i,j;
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            fscanf(fp, "%i%*c", &M[i][j]);
}

void StampaMatrice(int M[NR][NC], int nr, int nc){
    int i,j;
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            printf("%3i", M[i][j]);
        }
        printf("\n");
    }
}
