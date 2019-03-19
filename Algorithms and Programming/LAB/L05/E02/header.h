#ifndef E02_HEADER_H
#define E02_HEADER_H

#include <stdio.h>

#define N 3
#define MAXS 100

typedef struct {
    int a, b;
    char c;
    float d;
    char s[MAXS];
} Item;

int leggiFile(Item M[][N], int nr, int nc){
    int i,j;
    FILE *fp = NULL;

    if((fp = fopen("file.txt", "r")) == NULL)return -1;
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            fscanf(fp, "%d%d %c%f%s", &M[i][j].a, &M[i][j].b, &M[i][j].c, &M[i][j].d, M[i][j].s);
    fclose(fp);
}

void stampaItem(Item M[][N], int nr, int nc){
    int i,j;
    while(printf("Inserisci indici di riga e colonna: ") && scanf("%d%d%*c", &i, &j) && (i!=-1 && j!=-1)){
        if(i >= nr || j >= nc){
            printf("Inserire indice riga compreso tra 0 e %d e indice colonna compreso tra 0 e %d\n", nr, nc);
            continue;
        }
        printf("M[%d][%d]:\n", i,j);
        printf("\ta:%d\n", M[i][j].a);
        printf("\tb:%d\n", M[i][j].b);
        printf("\tc:%c\n", M[i][j].c);
        printf("\td:%f\n", M[i][j].d);
        printf("\ts:%s\n", M[i][j].s);
    }
}

#endif //E02_HEADER_H
