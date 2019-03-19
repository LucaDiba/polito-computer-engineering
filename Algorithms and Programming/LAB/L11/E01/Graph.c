#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Graph.h"
#include "PQ.h"

#define MAX 10
#define maxWT INT_MAX

struct graph {
    int V;
    int E;
    int **adj;
    int *vertici_eliminati;
    ST tab;
};

int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  for (i=0; i < r; i++)
    t[i] = malloc(c * sizeof(int));
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

void MATRIXfree(int **matrix, int r){
    int i;
    for(i=0; i<r; i++)
        free(matrix[i]);
    free(matrix);
}

ST getSTTab(Graph G){
  return G->tab;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->adj = MATRIXint(V, V, maxWT);
    G->tab = STinit(V);
    G->vertici_eliminati = calloc(G->V, sizeof(int));
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G){
    STfree(G->tab);
    MATRIXfree(G->adj, G->V);
    free(G->vertici_eliminati);
    free(G);
}

void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  if (G->adj[v][w] == maxWT)
    G->E++;
  G->adj[v][w] = wt;
  G->adj[w][v] = wt;
}

void GRAPHread(Graph G, FILE* fp) {
  int wt;
  char src[MAX], dst[MAX];

  while(fscanf(fp, "%s %s %d", src, dst, &wt) == 3) {
    int id1 = STsearch(G->tab, src);
    if (id1 == -1)
      id1 = STinsert(G->tab, src);

    int id2 = STsearch(G->tab, dst);
    if (id2 == -1)
      id2 = STinsert(G->tab, dst);

    if (id1 < 0 || id2 < 0)
      continue;

    insertE(G, EDGEcreate(id1, id2, wt));
  }
}

void GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=v+1; w < G->V; w++)
      if (G->adj[v][w] != maxWT)
        a[E++] = EDGEcreate(v, w, G->adj[v][w]);
}

void  GRAPHshow(Graph G) {
  int i, j;
  printf("Graph has %d vertices, %d edges \n", G->V, G->E);
  for (i=0; i < G->V; i++) {
    printf("%s:  ", STretrieve(G->tab, i));
    for (j=0; j < G->V; j++)
      if (G->adj[i][j] != maxWT)
        printf("(%s %d)", STretrieve(G->tab, j), G->adj[i][j]);
    printf("\n");
  }
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

void GRAPHmstK(Graph G, ST tab){
    int i, k, weight = 0;
    Edge *mst;
    mst = malloc(G->E * sizeof(Edge));

    k = mstE(G, mst);

    printf("\nEdges in the MST: \n");

    for (i=0; i < k; i++) {
        printf("(%s - %s) \n", STretrieve(tab, mst[i].v), STretrieve(tab, mst[i].w));
        weight += mst[i].wt;
    }
    printf("minimum weight: %d\n", weight);
}

void mstV(Graph G, int *st, int *wt) {
  int v, w, min, *fr;
  fr = malloc(G->V*sizeof(int));

  for ( v=0; v < G->V; v++) {
    st[v] = -1;
    fr[v] = v;
    wt[v] = maxWT;
  }
  st[0] = 0;
  wt[0] = 0;
  wt[G->V] = maxWT;

  for ( min = 0; min != G->V; ) {
    v = min;
    st[min] = fr[min];
    for (w = 0, min = G->V; w < G->V; w++)
      if (st[w] == -1) {
        if (G->adj[v][w] < wt[w]) {
          wt[w] = G->adj[v][w];
          fr[w] = v;
        }
        if (wt[w] < wt[min])
          min = w;
      }
  }
}

void GRAPHmstP(Graph G) {
  int v, *st, *wt, weight = 0;
  st = malloc(G->V*sizeof(int));
  wt = malloc((G->V+1)*sizeof(int));

  mstV(G, st, wt);

  printf("\nEdges in the MST: \n");

  for ( v=0; v < G->V; v++) {
    if (st[v] != v) {
      printf("(%s - %s) \n", STretrieve(G->tab, st[v]), STretrieve(G->tab, v));
      weight += wt[v];
    }
  }
  printf("\n");
  printf("minimum weight: %d\n", weight);
}

/* Dijkstra */
void GRAPHminDist(Graph G, int id_nodo){
    int v, w;
    PQ pq = PQinit(G->V);
    int *st, *d;
    st = malloc(G->V * sizeof(int));
    d  = malloc(G->V * sizeof(int));
    int s = id_nodo;
    for (v = 0; v < G->V; v++){
        st[v] = -1;
        d[v]  = maxWT;
        PQinsert(pq, d, v);
    }
    d[s] = 0;
    st[s] = s;
    PQchange(pq, d, s);
    while (!PQempty(pq)) {
    if (d[v = PQextractMin(pq, d)] != maxWT) {
        for (w = 0; w < G->V; w++) {
            if (G->adj[v][w] != maxWT){
                if (d[v] + G->adj[v][w] < d[w]) {
                    d[w] = d[v] + G->adj[v][w];
                    PQchange(pq, d, w);
                    st[w] = v;
                }
            }
        }
    }
    }
    printf("Distanza minima di %s da:\n", STretrieve(G->tab, s));
    for (v = 0; v < G->V; v++)
        if(v != id_nodo)
            printf("\t- %s: %d\n", STretrieve(G->tab, v), d[v]);
}

// Visita in profondita`
int isGraphAcyclicR(Graph G, Edge e, int *time, int *pre, int *post, int *st){
    int v, w = e.w;

    st[e.w] = e.v;
    pre[w] = (*time)++;
    for(v=0; v<G->V; v++)
        if(G->vertici_eliminati[v] == 0)
            if(G->adj[w][v] != maxWT){
                if(pre[v] == -1) {
                    if (isGraphAcyclicR(G, EDGEcreate(w, v, 1), time, pre, post, st) == 0)
                        return 0;
                }else if (pre[w] < pre[v]) { // arco back
                    return 0;
                }
            }
    return 1;
}

int isGraphAcyclic(Graph G){
    int v, time=0, *pre, *post, *st;
    pre  = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st   = malloc(G->V * sizeof(int));
    for(v=0; v<G->V; v++)
        if(G->vertici_eliminati[v] == 0)
            pre[v] = post[v] = st[v] = -1;
    for(v=0; v<G->V; v++)
        if(G->vertici_eliminati[v] == 0)
            if(pre[v] == -1)
                if(isGraphAcyclicR(G, EDGEcreate(v, v, 1), &time, pre, post, st) == 0)
                    return 0;
    return 1;
}

void aggiungiSoluzione(Graph G, soluzioni_vertici_t soluzioni_vertici, int *sol){
    int i;

    int n = soluzioni_vertici->n, m = soluzioni_vertici->m;
    if(n == m)
        soluzioni_vertici = realloc(soluzioni_vertici, (m *= 2) * sizeof(int));

    soluzioni_vertici->soluzioni[n] = malloc(G->V * sizeof(int));
    for(i=0; i<G->V; i++)
        soluzioni_vertici->soluzioni[n][i] = sol[i];

    n++;
    soluzioni_vertici->n = n;
    soluzioni_vertici->m = m;
}

int verificaGrafo(Graph G, soluzioni_vertici_t soluzioni_vertici, int *sol, int n){
    int i;

    for(i=0; i<G->V; i++)
        G->vertici_eliminati[i] = 0;
    for(i=0; i<n; i++)
        G->vertici_eliminati[sol[i]] = 1;

    if(isGraphAcyclic(G)){
        aggiungiSoluzione(G, soluzioni_vertici, G->vertici_eliminati);
        return 1;
    }else
        return 0;
}

// Powerset
int rendiGrafoAciclicoR(Graph G, soluzioni_vertici_t soluzioni_vertici, int* val, int k, int* sol, int n, int pos, int start){
    int i, flag = 0;

    if (pos == n)
        return verificaGrafo(G, soluzioni_vertici, sol, n);

    for (i = start; i < k; i++){
        sol[pos] = val[i];
        if(rendiGrafoAciclicoR(G, soluzioni_vertici, val, k, sol, n, pos+1, i+1))
            flag = 1;
    }
    return flag;
}

void rendiGrafoAciclico(Graph G, soluzioni_vertici_t soluzioni_vertici){
    int n;
    int *val = malloc(G->V * sizeof(int));
    int *sol = malloc(G->V * sizeof(int));

    for(n=0; n<G->V; n++)
        val[n] = n;

    if(isGraphAcyclic(G)){
        printf("Il grafo e` gia` aciclico. Non e` necessario eliminare vertici.\n");
        return;
    }

    for(n = 1; n <= G->V; n++){
        if(rendiGrafoAciclicoR(G, soluzioni_vertici, val, G->V, sol, n, 0, 0))
            break;
    }
}

soluzioni_vertici_t soluzioniVerticiInit(int n){
    soluzioni_vertici_t soluzioni_vertici = malloc(sizeof(soluzioni_vertici_t));
    soluzioni_vertici->soluzioni = malloc(n * sizeof(int));
    soluzioni_vertici->m = n;
    soluzioni_vertici->n = 0;
    return soluzioni_vertici;
}

void dfsRcc(Graph G, int v, int id, int *cc) {
    int i;
    cc[v] = id;
    for(i=0; i<G->V; i++)
        if(G->adj[v][i] != maxWT && G->vertici_eliminati[i] == 0)
            if(cc[i] == -1)
                dfsRcc(G, i, id, cc);
}

int GRAPHcc(Graph G){
    int v, id = 0, *cc;
    cc = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++)
        cc[v] = -1;

    for (v = 0; v<G->V; v++) {
        if (G->vertici_eliminati[v] == 0 && cc[v] == -1)
            dfsRcc(G, v, id++, cc);
    }

    return id;
} //componenti connesse

int GETwt(Graph G, int sc, int b){
    int v, w;

    PQ pq = PQinit( G->V );
    int *st, *d;
    st = malloc( G->V * sizeof( int ));
    d = malloc( G->V * sizeof( int ));

    for(v=0; v<G->V; v++){
        st[v]=-1;
        d[v] = maxWT;
        PQinsert(pq,d,v);
    }

    d [sc] = 0;
    st[sc] = sc;
    PQchange(pq,d,sc);

    while(!PQempty(pq)){
        if(d[v=PQextractMin(pq,d)]!=maxWT){
            for(w=0; w<G->V; w++)
                if(G->vertici_eliminati[w] == 0)
                    if(d[v] + G->adj[v][w] < d[w]){
                        d[w] =  + G->adj[v][w];
                        PQchange(pq, d, v);
                        st[w] = v;
                    }
        }
    }

    return d[b];
}

void comb_s(int start,int pos,int *val, int *sol, int n,int k,Graph C,Graph G){ //k=2 //val = insieme di vertici
    int i, wt, v = pos-1, w;
    int found = 0;
    if(pos>=k){
        wt = GETwt(G,sol[pos-1],sol[pos]);
        C->adj[sol[pos-1]][sol[pos]] = wt;
        C->adj[sol[pos]][sol[pos-1]] = wt;
        return;
    }
    for(i=start; i<n; i++){
        if(C->vertici_eliminati[i] == 0) {
            if (pos == k - 1) { //pruning
                for (w = 0; w < C->V; w++)
                    if (C->vertici_eliminati[w] == 0)
                        if (w == val[i])
                            found = 1;
            }
            if (!found && C->vertici_eliminati[pos] == 0) {
                sol[pos] = val[i];
                comb_s(i + 1, pos + 1, val, sol, n, k, C, G);
            }
        }
    }

}

void GRAPHconnect(Graph G, Graph C){
    int k=2, i;
    int *val = malloc(sizeof(int) * C->V);
    int *sol = calloc(sizeof(int),  k);

    for(i=0;i<C->V;i++)
        val[i]=i;

    comb_s(0, 0, val, sol, G->V, 2, C, G);

    GRAPHmstK(C,G->tab);
}

void GRAPHcpy(Graph C, Graph G, int*soluzione){
    int v, w;
    C->V = G->V;
    C->E = G->E;
    C->tab = G->tab;

    for(v=0; v<G->V; v++)
        if(soluzione[v] == 1)
            C->vertici_eliminati[v] = 1;

    for (v=0; v < G->V; v++)
        for (w=v+1; w < G->V; w++){
            C->adj[v][w] = G->adj[v][w];
            C->adj[w][v] = G->adj[v][w];
        }
}