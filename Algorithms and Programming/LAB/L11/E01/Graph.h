#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "UF.h"
#include "ST.h"

typedef struct graph *Graph;

/* STRUTTURA DATI "soluzioni_vertici"
 * n: numero soluzioni (tutti gli insiemi di cardinalita` minima che soddisfano le richieste)
 * m: dimensione vettore soluzioni
 * soluzioni: contiene m vettori (di cui n con soluzioni valide). All'indice del vettore corrisponde l'ID
 *            del vertice. Per ogni vertice, il valore e`:
 *                  - 0: se non deve essere eliminato
 *                  - 1: se deve essere eliminato
 *            Esempio: la soluzione [0, 0, 1, 0] elimina il terzo vertice (quello con id 2) e lascia tutti gli altri
 */
typedef struct soluzioni_vertici_s{
    int **soluzioni;
    int n, m;
}* soluzioni_vertici_t;

Graph GRAPHinit (int);
void  GRAPHfree (Graph);
void  GRAPHread (Graph, FILE*);
void  GRAPHcpy  (Graph C, Graph G, int*soluzione);
void  GRAPHedges(Graph, Edge *);
void  GRAPHshow (Graph);
void  GRAPHmstK(Graph G, ST tab);
void  GRAPHmstP (Graph G);
ST    getSTTab  (Graph G);
int   GRAPHcc     (Graph G);
void  GRAPHconnect(Graph G, Graph C);
void  GRAPHminDist(Graph G, int id_nodo);
int   GRAPHEdgesNumber  (Graph G);
void  rendiGrafoAciclico(Graph G, soluzioni_vertici_t);
int   isGraphAcyclic(Graph);
soluzioni_vertici_t soluzioniVerticiInit(int n);

#endif
