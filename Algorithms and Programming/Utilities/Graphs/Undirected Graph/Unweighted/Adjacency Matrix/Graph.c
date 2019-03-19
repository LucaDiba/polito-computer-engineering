#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#define MAX 10

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
  G->adj = MATRIXint(V, V, 0);
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  if (G->adj[v][w] == 0)
    G->E++;
  G->adj[v][w] = 1;
  G->adj[w][v] = 1;
}

void GRAPHread(Graph G) {
  char name[MAX], src[MAX], dst[MAX];
  FILE *fin;
  printf("Input file name: ");
  scanf("%s", name);
  fin = fopen(name, "r");
  if (fin == NULL)
    exit(-1);
  while(fscanf(fin, "%s %s", src, dst) == 2) {

    int id1 = STsearch(G->tab, src);
    if (id1 == -1)
      id1 = STinsert(G->tab, src);

    int id2 = STsearch(G->tab, dst);
    if (id2 == -1)
      id2 = STinsert(G->tab, dst);

    if (id1 < 0 || id2 < 0)
      continue;

    insertE(G, EDGEcreate(id1, id2));
  }
  return;
}

void GRAPHwrite(Graph G) {
  int i;
  char name[MAX];
  FILE *fout;
  Edge a[G->E];
  printf("Input file name: ");
  scanf("%s", name);
  fout = fopen(name, "w");
  if (fout == NULL)
    exit(-1);
  GRAPHedges(G, a);
  for (i = 0; i < G->E; i++)
    fprintf(fout, "%s  %s\n", STretrieve(G->tab, a[i].v),STretrieve(G->tab, a[i].w));
  fclose(fout);
  return;
}

void GRAPHinsert(Graph G) {
  char src[MAX], dst[MAX];

  printf("Insert first node = ");
  scanf("%s", src);
  printf("Insert second node = ");
  scanf("%s", dst);

  int id1 = STsearch(G->tab, src);
  if (id1 == -1)
    id1 = STinsert(G->tab, src);

  int id2 = STsearch(G->tab, dst);
  if (id2 == -1)
    id2 = STinsert(G->tab, dst);

  if (id1 < 0 || id2 < 0)
      return;

  insertE(G, EDGEcreate(id1, id2));
  return;
}

void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->adj[v][w] == 1)
    G->E--;
  G->adj[v][w] = 0;
  G->adj[w][v] = 0;
}

void GRAPHremove(Graph G) {
  char src[MAX], dst[MAX];

  printf("Insert first node = ");
  scanf("%s", src);
  printf("Insert second node = ");
  scanf("%s", dst);

  int id1 = STsearch(G->tab, src);
  int id2 = STsearch(G->tab, dst);

  if (id1 < 0 || id2 < 0)
      return;

  removeE(G, EDGEcreate(id1, id2));
  return;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=v+1; w < G->V; w++)
      if (G->adj[v][w] == 1)
        a[E++] = EDGEcreate(v, w);
  return;
}

void  GRAPHshow(Graph G) {
  int i, j;
  printf("Graph has %d vertices, %d edges \n", G->V, G->E);
  for (i=0; i < G->V; i++) {
    printf("%s:  ", STretrieve(G->tab, i));
    for (j=0; j < G->V; j++)
      if (G->adj[i][j])
        printf("%s ", STretrieve(G->tab, j));
    printf("\n");
  }
}

int pathR(Graph G, int v, int w, int *visited) {
  int t;
  if (v == w)
    return 1;
  visited[v] = 1;
  for ( t = 0 ; t < G->V ; t++)
    if (G->adj[v][t] == 1)
      if (visited[t] == 0)
        if (pathR(G, t, w, visited)) {
          printf("edge (%s, %s) belongs to path \n", STretrieve(G->tab, v), STretrieve(G->tab, t));
          return 1;
        }
  return 0;
}

int GRAPHpath(Graph G) {
  int t, found, *visited;
  char src[MAX], dst[MAX];

  visited = malloc(G->V*sizeof(int));
  for ( t = 0 ; t < G->V ; t++)
    visited[t] = 0;

  printf("Insert first node = ");
  scanf("%s", src);
  printf("Insert second node = ");
  scanf("%s", dst);

  int id1 = STsearch(G->tab, src);
  int id2 = STsearch(G->tab, dst);

  if (id1 < 0 || id2 < 0)
      return 0;

  found = pathR(G, id1, id2, visited);
  if (found == 0)
    printf("\n Path not found!\n");
  return found;
}


int pathRH(Graph G, int v, int w, int d, int *visited) {
  int t;
  if (v == w) {
    if (d == 0)
      return 1;
    else
      return 0;
  }
  visited[v] = 1;
  for ( t = 0 ; t < G->V ; t++)
  if (G->adj[v][t] == 1)
    if (visited[t] == 0)
      if (pathRH(G, t, w, d-1, visited)) {
        printf("edge (%s, %s) belongs to path \n", STretrieve(G->tab, v), STretrieve(G->tab, t));
        return 1;
      }
  visited[v] = 0;
  return 0;
}

int GRAPHpathH(Graph G) {
  int t, found, *visited;
  char src[MAX], dst[MAX];

  visited = malloc(G->V*sizeof(int));
  for ( t = 0 ; t < G->V ; t++)
    visited[t] = 0;

  printf("Insert first node = ");
  scanf("%s", src);
  printf("Insert second node = ");
  scanf("%s", dst);

  int id1 = STsearch(G->tab, src);
  int id2 = STsearch(G->tab, dst);

  if (id1 < 0 || id2 < 0)
      return 0;

  found = pathRH(G, id1, id2, G->V-1, visited);
  if (found == 0)
    printf("\n Hamiltonian path not found!\n");
  return found;
}


void bfs(Graph G, Edge e, int *time, int *pre, int *st) { // funzione iterativa, non ricorsiva
  int v;
  Q q = Qinit();
  Qput(q, e);
  while (!Qempty(q))
    if (pre[(e = Qget(q)).w] == -1) { // stiamo considerando un vertice nuovo (nodo ancora da scoprire)
      pre[e.w] = (*time)++;
      st[e.w] = e.v; // suo padre e` e.v
      for (v = 0; v < G->V; v++)         // prendiamo tutti i vertici adiacenti
        if (G->adj[e.w][v] == 1)         // se esiste l'arco
          if (pre[v] == -1)              // se arco mi porta in nodi ancora da scoprire
            Qput(q, EDGEcreate(e.w, v)); // ricreo l'arco corrispondente e lo inserisco in coda
    }
}

void GRAPHbfs(Graph G) {
  int v, time=0, *pre, *st;
  pre = malloc(G->V*sizeof(int));
  st = malloc(G->V*sizeof(int));

  for (v=0; v < G->V; v++) {
    pre[v] = -1;
    st[v] = -1;
  }
  bfs(G, EDGEcreate(0,0), &time, pre, st);

  printf("\n Resulting BFS tree \n");
  for (v=0; v < G->V; v++)
    if (st[v] != -1)
      printf("%s's parent is: %s\n", STretrieve(G->tab, v), STretrieve(G->tab, st[v]));
}





