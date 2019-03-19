#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "ST.h"
#include "Item.h"

void leggiVertici(FILE*, ST, int N);

int main() {
    int V, matrice_generata = 0, selezione, id_elaboratore_st;
    char buff[MAX_N+1];
    Edge *edges;
    FILE *fp = NULL;
    Graph G;
    ST st;
    flussi_t flussi;

    fp = fopen("grafo.txt", "r");
    fscanf(fp, "%d", &V);
    G = GRAPHinit(V);
    st = getSTFromGraph(G);
    leggiVertici(fp, st, V);
    GRAPHread(G, fp);
    edges = malloc(GRAPHedgesN(G) * sizeof(*edges));
    //GRAPHedges(G, edges);
    while(1){
        printf("1. Stampa vertici\n"
               "2. Stampa numero archi incidenti e vertici connessi\n"
               "3. Genera la matrice di adiacenza\n"
               "4. Determina flussi intra- ed inter-rete\n"
               "5. Esci");
        scanf("%d", &selezione);
        if(selezione == 5) {
            break;
        }else if(selezione == 1){
            stampaVertici(st);
        }else if(selezione == 2){
            printf("Inserisci nome elaboratore: ");
            scanf("%s", buff);
            id_elaboratore_st = STsearchID(st, buff);
            printf("Ci sono %d archi incidenti\n", numeroArchiIncidenti(edges, G, id_elaboratore_st));
            printf("Elenco vertici connessi:\n");
            stampaVerticiConnessi(id_elaboratore_st, G);
        }else if(selezione == 3){
            if(matrice_generata == 0) {
                GRAPHListToMatrix(G);
                printf("Matrice delle adiacenze generata correttamente.\n");
                matrice_generata = 1;
            }else{
                printf("La matrice delle adiacenze era gia` stata generata.\n");
            }
        }else if(selezione == 4){
            flussi = determinaFlussi(edges, G);
            printf("Sono presenti:\n"
                           "- %d flussi inter-rete\n"
                           "- %d flussi intra-rete\n", flussi.inter, flussi.intra);
        }else{
            printf("Selezione non valida.\n");
        }
    }

    return 0;
}

void leggiVertici(FILE* fp, ST st, int N){
    char nome[MAX_N+1], id_rete[MAX_R+1];
    int i;

    for(i=0; i<N; i++){
        fscanf(fp, " %s %s", nome, id_rete);
        STinsert(st, ITEMnew(nome, id_rete));
    }
}