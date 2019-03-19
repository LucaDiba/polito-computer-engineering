#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"

#define MAX 10
#define maxWT INT_MAX

typedef struct node *link;
struct node{
    int v;
    int wt;
    link next;
};
struct graph {
    int V;
    int E;
    link *adj_list;
    int **adj_mtx;
    ST tab;
    link z;
};

int GRAPHedgesN(Graph G){
    return G->E;
}

link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    if(x == NULL){
        printf("Errore allocazione link");
        exit(EXIT_FAILURE);
    }
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

ST getSTFromGraph(Graph G){
    return G->tab;
}

void GRAPHListToMatrix(Graph G){
    int i, v;
    link t;

    G->adj_mtx = calloc(G->V, sizeof(int*));
    for(i=0; i<G->V; i++)
        G->adj_mtx[i] = calloc(G->V, sizeof(int));

    for (v=0; v < G->V; v++)
        for (t=G->adj_list[v]; t != G->z; t = t->next)
            G->adj_mtx[v][t->v] = t->wt;
}

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    if (G == NULL){
        printf("Errore allocazione grafo");
        exit(1);
    }

    G->V = V;
    G->E = 0;
    G->z = NEW(-1, 0, NULL);
    G->adj_list = malloc(G->V*sizeof(link));
    if(G->adj_list == NULL){
        printf("Errore allocazione lista adj ");
        exit(1);
    }
    for (v = 0; v < G->V; v++)
        G->adj_list[v] = G->z;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}
void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;

    G->adj_list[v] = NEW(w, wt, G->adj_list[v]);
    G->adj_list[w] = NEW(v, wt, G->adj_list[w]);
    G->E++;
}

void GRAPHread(Graph G, FILE* fp) {
    int wt, i=0;
    char src[MAX], dst[MAX];

    while(fscanf(fp, " %s %s %d", src, dst, &wt) == 3){
        int id1 = STsearchID(G->tab, src);
        if (id1 == -1){
            printf("Trovato vertice %s non letto", src);
            exit(1);
        }
        int id2 = STsearchID(G->tab, dst);
        if (id2 == -1){
            printf("Trovato vertice %s non letto", dst);
            exit(1);
        }
        if (id1 < 0 || id2 < 0)
            continue;
        insertE(G, EDGEcreate(id1, id2, wt));
    }
}

void  GRAPHshow(Graph G) {
    int v;
    link t;
    printf("%d vertices, %d edges \n", G->V, G->E);
    for (v=0; v < G->V; v++) {
        printf("%s:\t", KEYget(STretrieve(G->tab, v)));
        for (t=G->adj_list[v]; t != G->z; t = t->next)
            printf("(%s  %d)", KEYget(STretrieve(G->tab, t->v)), t->wt);
        printf("\n");
    }
}

void  GRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    link t;
    for (v=0; v < G->V; v++)
        for (t=G->adj_list[v]; t != G->z; t = t->next)
            if (v < t->v)
                a[E++] = EDGEcreate(v, t->v, t->wt);
}

void sort(Edge *a, int l, int r ) {
    int i, j, min, temp;
    for(i = l; i < r; i++) {
        min = i;
        for (j = i+1; j <= r; j++)
            if (a[j].wt < a[min].wt)
                min = j;

        temp = a[i].v;
        a[i].v = a[min].v;
        a[min].v = temp;

        temp = a[i].w;
        a[i].w = a[min].w;
        a[min].w = temp;

        temp = a[i].wt;
        a[i].wt = a[min].wt;
        a[min].wt = temp;
    }
}


int mstE(Graph G, Edge *mst) {
    int i, k;
    Edge a[G->E];
    GRAPHedges(G, a);

    sort(a, 0, G->E-1);

    UFinit(G->V);

    for ( i=0, k=0; i < G->E && k < G->V-1; i++ )
        if (!UFfind(a[i].v, a[i].w)) {
            UFunion(a[i].v, a[i].w);
            mst[k++] = a[i];
        }
    return k;
}

void GRAPHmstK(Graph G) {
    int i, k, weight = 0;
    Edge *mst;
    mst = malloc(G->E * sizeof(Edge));
    if(mst == NULL){
        printf("Errore in alloazione arco");
        exit(1);
    }

    k = mstE(G, mst);

    printf("\nEdges in the MST: \n");

    for (i=0; i < k; i++) {
        printf("(%s - %s) \n", KEYget(STretrieve(G->tab, mst[i].v)), KEYget(STretrieve(G->tab, mst[i].w)));
        weight += mst[i].wt;
    }
    printf("minimum weight: %d\n", weight);
}

flussi_t determinaFlussi(Edge* e, Graph G){
    flussi_t flussi;
    int intra=0, inter=0, i;
    char *rete_1, *rete_2;

    for(i=0; i<G->E; i++) {
        rete_1 = getRete(STretrieve(G->tab, e[i].v));
        rete_2 = getRete(STretrieve(G->tab, e[i].w));
        if (strcmp(rete_1, rete_2) == 0) {
            intra += e[i].wt;
        } else {
            inter += e[i].wt;
        }
    }
    flussi.intra = intra;
    flussi.inter = inter;
    return flussi;
}

void stampaVertici(ST st){
    int i, n=STcount(st);
    for(i=0; i<n; i++)
        printf("- %s\n", KEYget(STretrieve(st, i)));
}

int numeroArchiIncidenti(Edge* e, Graph G, int id_elaboratore_st){
    int i, cnt=0;
    for(i=0; i<G->E; i++){
        if(e[i].w == id_elaboratore_st || e[i].v == id_elaboratore_st)
            cnt++;
    }
    return cnt;
}

void  stampaVerticiConnessi(int id_elaboratore_st, Graph G){
    int v = id_elaboratore_st;
    link t;

    for (t=G->adj_list[v]; t != G->z; t = t->next)
        printf("(%s  %d) ", KEYget(STretrieve(G->tab, t->v)), t->wt);
    printf("\n");
}