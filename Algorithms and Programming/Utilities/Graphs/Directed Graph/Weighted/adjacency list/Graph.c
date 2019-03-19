#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"
#include "PQ.h"

#define maxWT INT_MAX
#define MAX 10

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *adj; ST tab; link z; } ;

link NEW(int v, int wt, link next) {
  link x = malloc(sizeof *x);
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
  G->E++;
}

void GRAPHread(Graph G) {
  char name[MAX], src[MAX], dst[MAX];
  int wt;
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

void GRAPHinsert(Graph G) {
  char src[MAX], dst[MAX];
  int id1, id2, wt;

  printf("Insert first node = ");
  scanf("%s", src);
  printf("Insert second node = ");
  scanf("%s", dst);
  printf("Insert weight = ");
  scanf("%d", &wt);

  id1 = STsearch(G->tab, src);
  if (id1 == -1)
    id1 = STinsert(G->tab, src);

  id2 = STsearch(G->tab, dst);
  if (id2 == -1)
    id2 = STinsert(G->tab, dst);

  if (id1 < 0 || id2 < 0)
      return;

  insertE(G, EDGEcreate(id1, id2, wt));
  return;
}

void  GRAPHshow(Graph G) {
  int v;
  link t;
  printf("%d vertices, %d edges \n", G->V, G->E);
  for (v=0; v < G->V; v++) {
    printf("%s:\t", STretrieve(G->tab, v));
    for (t=G->adj[v]; t != G->z; t = t->next)
      printf("%s/%d  ", STretrieve(G->tab, t->v), t->wt);
    printf("\n");
  }
}

void GRAPHspD(Graph G) {
  int v, w; link t;
  char name[MAX];
  PQ pq = PQinit(G->V);
  int *st, *mindist;
  st = malloc(G->V*sizeof(int));
  mindist = malloc(G->V*sizeof(int));

  printf("Insert start node: ");
  scanf("%s", name);

  int s = STsearch(G->tab, name);
  if (s == -1) {
    printf("Node doesn't exist\n");
    return;
  }

  for (v = 0; v < G->V; v++){
    st[v] = -1;
    mindist[v] = maxWT;
    PQinsert(pq, mindist, v);
  }

  mindist[s] = 0;
  st[s] = s;
  PQchange(pq, mindist, s);

  while (!PQempty(pq)) {
    if (mindist[v = PQextractMin(pq, mindist)] != maxWT) {
      for (t=G->adj[v]; t!=G->z ; t=t->next)
        if (mindist[v] + t->wt < mindist[w=t->v]) {
          mindist[w] = mindist[v] + t->wt;
          PQchange(pq, mindist, w);
          st[w] = v;
        }
    }
  }

  printf("\n Shortest path tree\n");
  for (v = 0; v < G->V; v++)
    printf("parent of %s is %s \n", STretrieve(G->tab, v), STretrieve(G->tab, st[v]));

  printf("\n Minimum distances from node %s\n", STretrieve(G->tab, s));
  for (v = 0; v < G->V; v++)
    printf("mindist[%s] = %d \n", STretrieve(G->tab, v), mindist[v]);
}

void GRAPHspBF(Graph G){
  int v, w, negcycfound;
  link t;
  char name[MAX];
  int *st, *mindist;

  st = malloc(G->V*sizeof(int));
  mindist = malloc(G->V*sizeof(int));

  printf("Insert start node: ");
  scanf("%s", name);

  int s = STsearch(G->tab, name);
  if (s == -1) {
    printf("Node doesn't exist\n");
    return;
  }

  for ( v = 0; v < G->V; v++) {
    st[v]= -1;
    mindist[v] = maxWT;
  }

  mindist[s] = 0;
  st[s] = s;

  for (w = 0; w < G->V - 1; w++)
    for (v = 0; v < G->V; v++)
      if (mindist[v] < maxWT)
        for (t = G->adj[v]; t != G->z ; t = t->next)
          if (mindist[t->v] > mindist[v] + t->wt) {
            mindist[t->v] = mindist[v] + t->wt;
            st[t->v] = v;
          }
  negcycfound = 0;
  for (v = 0; v < G->V; v++)
    if (mindist[v] < maxWT)
      for (t = G->adj[v]; t != G->z ; t = t->next)
        if (mindist[t->v] > mindist[v] + t->wt)
          negcycfound = 1;
  if (negcycfound == 0) {
    printf("\n Shortest path tree\n");
    for (v = 0; v < G->V; v++)
      printf("Parent of %s is %s \n", STretrieve(G->tab, v), STretrieve(G->tab, st[v]));

    printf("\n Minimum distances from node %s\n", STretrieve(G->tab, s));
    for (v = 0; v < G->V; v++)
      printf("mindist[%s] = %d \n", STretrieve(G->tab, v), mindist[v]);
  }
  else
    printf("\n Negative cycle found!\n");
}
