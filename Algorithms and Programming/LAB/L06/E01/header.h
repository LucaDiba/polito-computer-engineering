#ifndef E01_HEADER_H
#define E01_HEADER_H

#include <stdio.h>
#include <malloc.h>
#include <mem.h>
#include <math.h>
#include <ctype.h>

#define N 30
typedef struct {
    char *nome;
    int prezzo; //in centesimi
} Prodotto;

int leggiFile(char*, Prodotto**);
int stringToCentesimi(char *);

void powerset(Prodotto* val, int n, int card_min, int importo_max);
void powerset_r(Prodotto* val, int importo, int importo_max, int k, int* sol, int n, int pos, int start);


int leggiFile(char *nomeFile, Prodotto **passed_prodotti){
    FILE *fp = NULL;
    int i,n_prodotti,tmp;
    char buff[N+1], buff_prezzo[5+1];
    Prodotto *prodotti = NULL;

    if((fp=fopen(nomeFile, "r")) == NULL)return -1;
    fscanf(fp, "%d", &n_prodotti);
    prodotti = malloc(n_prodotti * sizeof(Prodotto));
    for(i=0; i<n_prodotti; i++){
        fscanf(fp, "%*c%s %s", buff, buff_prezzo);
        tmp = stringToCentesimi(buff_prezzo);
        prodotti[i].prezzo = tmp;
        prodotti[i].nome = malloc((strlen(buff)+1) * sizeof(char));
        strcpy(prodotti[i].nome, buff);
    }
    fclose(fp);
    *passed_prodotti = prodotti;
    return  n_prodotti;
}
int stringToCentesimi(char *prezzo){
    int i,power,pow_max,centesimi=0, len=strlen(prezzo);
    for(i=0; prezzo[i] != '.' && i<len; i++); //trovo il punto
    pow_max = i = i+2; //mi posiziono sulla seconda cifra decimale

    for(power=0; power < pow_max; i--){
        if(prezzo[i] != '.') {
            centesimi += (prezzo[i] - '0') * pow(10, power);
            power++;
        }
    }
    return centesimi;
}
void powerset(Prodotto* val, int n, int card_min, int importo_max){
    int i, *sol;

    sol = malloc(n * sizeof(int));

    if(card_min == 0) {
        // INSIEME VUOTO
        printf("{ }\n");
    }

    for(i = card_min; i <= n; i++){
        powerset_r(val, 0, importo_max, n, sol, i, 0, 0);
    }
}
void powerset_r(Prodotto* val, int importo, int importo_max, int k, int* sol, int n, int pos, int start){
    int i;
    if(importo <= importo_max) {
        if (pos == n) {
            printf("{ ");
            for (i = 0; i < n; i++)
                printf("%s ", val[sol[i]].nome);
            printf(" } Totale: %.2f\n", (float) importo / 100);
            return;
        }
        for (i = start; i < k; i++) {
            sol[pos] = i;
            importo += val[i].prezzo;
            powerset_r(val, importo, importo_max, k, sol, n, pos + 1, i + 1);
            importo = 0;
        }
    }
}

#endif //E01_HEADER_H