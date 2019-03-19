#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"

#define MAX 10
#define maxWT INT_MAX

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *adj; ST tab; link z; } ;

link NEW(int v, int wt, link next) { link x = malloc(sizeof *x);
  x->v = v;
  x->wt = wt;
  x->next = next;
  return x;
}

Graph GRAPHinit(int V) {
  int v;
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;

  G->V = V;
  G->E = 0;
  G->z = NEW(-1, 0, NULL);
  G->adj = malloc(G->V*sizeof(link));
  for (v = 0; v < G->V; v++)
    G->adj[v] = G->z;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}
void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  G->adj[v] = NEW(w, wt, G->adj[v]);
  G->adj[w] = NEW(v, wt, G->adj[w]);
  G->E++;
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


void  GRAPHshow(Graph G) {
  int v;
  link t;
  printf("%d vertices, %d edges \n", G->V, G->E);
  for (v=0; v < G->V; v++) {
    printf("%s:\t", STretrieve(G->tab, v));
    for (t=G->adj[v]; t != G->z; t = t->next)
      printf("(%s  %d)", STretrieve(G->tab, t->v), t->wt);
    printf("\n");
  }
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, E = 0;
  link t;
  for (v=0; v < G->V; v++)
    for (t=G->adj[v]; t != G->z; t = t->next)
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
  Edge *mst;
  mst = malloc(G->E * sizeof(Edge));

  k = mstE(G, mst);

  printf("\nEdges in the MST: \n");

  for (i=0; i < k; i++) {
    printf("(%s - %s) \n", STretrieve(G->tab, mst[i].v), STretrieve(G->tab, mst[i].w));
    weight += mst[i].wt;
  }
  printf("minimum weight: %d\n", weight);
}

