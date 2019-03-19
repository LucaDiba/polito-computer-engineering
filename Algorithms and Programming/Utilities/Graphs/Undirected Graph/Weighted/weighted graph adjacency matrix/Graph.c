#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Graph.h"

#define MAX 10
#define maxWT INT_MAX

struct graph {int V; int E; int **adj; ST tab; };

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

Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->adj = MATRIXint(V, V, maxWT);
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  if (G->adj[v][w] == maxWT)
    G->E++;
  G->adj[v][w] = wt;
  G->adj[w][v] = wt;
}

void GRAPHread(Graph G) {
  int wt;
  char name[MAX], src[MAX], dst[MAX];
  FILE *fin;

  printf("Input file name: ");
  scanf("%s", name);
  fin = fopen(name, "r");
  if (fin == NULL)
    exit(-1);

  while(fscanf(fin, "%s %s %d", src, dst, &wt) == 3) {

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
  return;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=v+1; w < G->V; w++)
      if (G->adj[v][w] != maxWT)
        a[E++] = EDGEcreate(v, w, G->adj[v][w]);
  return;
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
  return;
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
  Edge *mst = malloc(G->E * sizeof(Edge));

  k = mstE(G, mst);

  printf("\nEdges in the MST: \n");

  for (i=0; i < k; i++) {
    printf("(%s - %s) \n", STretrieve(G->tab, mst[i].v), STretrieve(G->tab, mst[i].w));
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


