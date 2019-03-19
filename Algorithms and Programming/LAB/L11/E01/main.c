#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define MAX_N 30

int main() {
    int V, i, j, cc;
    char buff[MAX_N+1];
    Graph G, C; // il secondo grafo viene utilizzato soltanto al passo finale, per mantenere la modularita` di Graph.c
    ST st;
    FILE *fp = NULL;
    soluzioni_vertici_t soluzioni_vertici = soluzioniVerticiInit(1);

    if((fp=fopen("grafo.txt", "r")) == NULL){
        printf("Errore lettura file grafo");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", &V);
    G = GRAPHinit(V);
    st = getSTTab(G);

    for(i=0; i<V; i++){
        fscanf(fp, "%s", buff);
        STinsert(st, buff);
    }

    GRAPHread(G, fp);

    /* calcolo della distanza minima tra ogni coppia di nodi presenti all’interno del grafo */
    for(i=0; i<V; i++){
        GRAPHminDist(G, i);
    }

    /* individuazione di tutti gli insiemi di vertici di cardinalità minima la cui rimozione renda il grafo originale aciclico */
    rendiGrafoAciclico(G, soluzioni_vertici);

    printf("Soluzioni a cardinalita` minima:\n");
    for(i=0; i<soluzioni_vertici->n; i++){
        for(j=0; j<V; j++)
            if(soluzioni_vertici->soluzioni[i][j])
                printf("%s ", STretrieve(st, j));
        printf("\n");
    }

    for(i=0; i<soluzioni_vertici->n; i++){
        C = GRAPHinit(V);
        GRAPHcpy(C, G, soluzioni_vertici->soluzioni[i]);
        printf("\nSoluzione #%d\n", i+1);
        if ((cc=GRAPHcc(C)) == 1){
            printf("Il grafo e` connesso\n");
        }else{
            printf("Il grafo non e` conesso (%d componenti)\n", cc);
            GRAPHconnect(G, C);
        }
        GRAPHfree(C);
    }

    GRAPHfree(G);
    return 0;
}


