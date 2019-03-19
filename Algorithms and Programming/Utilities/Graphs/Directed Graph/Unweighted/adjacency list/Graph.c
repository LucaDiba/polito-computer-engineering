#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"

#define MAX 10

typedef struct node *link;
struct node { int v; link next; } ;
struct graph { int V; int E; link *adj; ST tab; link z; } ;

link NEW(int v, link next) { link x = malloc(sizeof *x);
  x->v = v; x->next = next;
  return x;
}

Graph GRAPHinit(int V) {
  int v;
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;

  G->V = V;
  G->E = 0;
  G->z = NEW(-1, NULL);
  G->adj = malloc(G->V*sizeof(link));
  for (v = 0; v < G->V; v++)
    G->adj[v] = G->z;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  G->adj[v] = NEW(w, G->adj[v]);
  G->E++;
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

void  GRAPHshow(Graph G) {
  int v;
  link t;
  printf("%d vertices, %d edges \n", G->V, G->E);
  for (v=0; v < G->V; v++) {
    printf("%s:\t", STretrieve(G->tab, v));
    for (t=G->adj[v]; t != G->z; t = t->next)
      printf("%s  ", STretrieve(G->tab, t->v));
    printf("\n");
  }
}

void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  link x;
  if (G->adj[v]->v == w) {
    G->adj[v] = G->adj[v]->next;
    G->E--;
  }
  else
    for (x = G->adj[v]; x != G->z; x = x->next)
      if (x->next->v == w) {
        x->next = x->next->next;
        G->E--;
  }
}

void GRAPHremove(Graph G) {
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

  if (id1 < 0 || id2 < 0) {
    printf("Edge doesn't exist\n");
    return;
  }
  else
    removeE(G, EDGEcreate(id1, id2));
  return;
}

void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st) {
  link t; int v, w = e.w; Edge x;
  if (e.v != e.w) // arco significativo (non cappio)
    printf("edge (%s, %s) is tree \n", STretrieve(G->tab, e.v), STretrieve(G->tab, e.w));
  st[e.w] = e.v;
  pre[w] = (*time)++;
  for (t = G->adj[w]; t != G->z; t = t->next) // nodi adiacenti al nodo corrente
    if (pre[t->v] == -1) // se vertice non ancora scoperto
      dfsR(G, EDGEcreate(w, t->v), time, pre, post, st); // riparte visita in profondita` da questo vertice
    else { // se vertice gia` scoperto
      v = t->v;
      x = EDGEcreate(w, v);
      if (post[v] == -1)
        printf("edge (%s, %s) is back \n", STretrieve(G->tab, x.v), STretrieve(G->tab, x.w));
      else
        if(pre[v]>pre[w])
          printf("edge (%s, %s) is forward \n", STretrieve(G->tab, x.v), STretrieve(G->tab, x.w));
        else
          printf("edge (%s, %s) is cross \n", STretrieve(G->tab, x.v), STretrieve(G->tab, x.w));
    }
  post[w] = (*time)++;
}

void GRAPHdfs(Graph G) {
  int v, time=0, *pre, *post, *st;
  pre = malloc(G->V * sizeof(int));
  post = malloc(G->V * sizeof(int));
  st = malloc(G->V * sizeof(int));

  for (v=0; v < G->V; v++) {
    pre[v] = -1;
    post[v] = -1;
    st[v] =  -1;
  }
  for (v=0; v < G->V; v++)
    if (pre[v]== -1)
      dfsR(G, EDGEcreate(v,v), &time, pre, post, st);

  printf("discovery/endprocessing time labels \n");
  for (v=0; v < G->V; v++)
    printf("vertex %s : %d/%d \n", STretrieve(G->tab, v), pre[v], post[v]);

  printf("resulting DFS tree \n");
  for (v=0; v < G->V; v++)
     printf("parent of vertex %s is vertex  %s \n", STretrieve(G->tab, v), STretrieve(G->tab, st[v]));
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, E = 0;
  link t;
  for (v=0; v < G->V; v++)
    for (t=G->adj[v]; t != G->z; t = t->next)
      if (v < t->v)
        a[E++] = EDGEcreate(v, t->v);
}

Graph GRAPHreverse(Graph G) {
  int v;
  link t;
  Graph R = GRAPHinit(G->V);
  for (v=0; v < G->V; v++)
    for (t= G->adj[v]; t != G->z; t = t->next)
      insertE(R, EDGEcreate(t->v, v));
  return R;
}

void SCCdfsR(Graph G, int w, int *scc, int *time0, int time1, int *post) {
  link t;
  scc[w] = time1;
  for (t = G->adj[w]; t != G->z; t = t->next)
    if (scc[t->v] == -1)
      SCCdfsR(G, t->v, scc, time0, time1, post);
  post[(*time0)++]= w;
}

int GRAPHscc(Graph G) {
  int v, time0 = 0, time1 = 0, *sccG, *sccR, *postG, *postR;
  Graph R = GRAPHreverse(G);

  sccG = malloc(G->V * sizeof(int));
  sccR = malloc(G->V * sizeof(int));
  postG = malloc(G->V * sizeof(int));
  postR = malloc(G->V * sizeof(int));

  for (v=0; v < G->V; v++) {
    sccG[v] = -1;
    sccR[v] = -1;
    postG[v] = -1;
    postR[v] = -1;
  }

  for (v=0; v < G->V; v++)
    if (sccR[v] == -1)
      SCCdfsR(R, v, sccR, &time0, time1, postR);

  time0 = 0;
  time1 = 0;

  for (v = G->V-1; v >= 0; v--)
    if (sccG[postR[v]]==-1){
      SCCdfsR(G,postR[v], sccG, &time0, time1, postG);
      time1++;
    }
  printf("strongly connected components \n");
  for (v = 0; v < G->V; v++)
    printf("node %d in scc %d \n", v, sccG[v]);
  return time1;
 }
