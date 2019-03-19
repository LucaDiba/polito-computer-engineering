#ifndef ESERCIZIO3_HEADER_H
#define ESERCIZIO3_HEADER_H

#include <stdio.h>
#include <mem.h>
#include <ctype.h>
#include <malloc.h>

#define N 30

typedef struct {
    int *scelte, num_scelte;
} Livello;

int leggiFile(char *, char ***);
void stringGenerator(int, char ***);
int princ_molt(int pos, Livello *val, int *sol, int n, int count);
void stampa(int *sol,  int n);

void stringGenerator(int nr, char ***passed_set){
    int i, j, *sol, count=0;
    Livello *val;
    char **set = *passed_set;


    val = malloc(nr * sizeof(*val));
    for(i=0; i<nr; i++) {
        val[i].num_scelte = strlen(set[i]);
        val[i].scelte = malloc(val[i].num_scelte * sizeof(int));
        for (j = 0; j < strlen(set[i]); j++)
            val[i].scelte[j] = (int) set[i][j];
    }

    if((sol=malloc(nr * sizeof(*sol))) == NULL)return;
    princ_molt(0, val, sol, nr, count);
}

int leggiFile(char* nomeFile, char*** set){
    FILE *fp;
    int i,nr;
    char buff[N+1], **tmp = NULL;

    if((fp=fopen(nomeFile, "r"))==NULL)return -1;

    fscanf(fp, "%d%*c", &nr);
    tmp = (char**) malloc(nr * sizeof(char*));
    for(i=0;i<nr;i++){
        fscanf(fp, "%s", buff);
        tmp[i] = (char*) malloc((strlen(buff)+1) * sizeof(char));
        strcpy(tmp[i], buff);
    }
    fclose(fp);
    *set = tmp;
    return nr;
}

int princ_molt(int pos, Livello *val, int *sol, int n, int count) {
    int i;
    if (pos >= n) {
        stampa(sol, n);
        printf("\n");
        return count+1;
    }
    for (i = 0; i < val[pos].num_scelte; i++) {
        sol[pos] = val[pos].scelte[i];
        count = princ_molt(pos+1, val, sol, n, count);
    }
    return count;
}

void stampa(int *sol,  int n){
    for (int i = 0; i < n; i++)
        printf("%c ", (char)(sol[i]));
}

#endif //ESERCIZIO3_HEADER_H