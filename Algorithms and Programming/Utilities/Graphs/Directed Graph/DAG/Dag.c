#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dag.h"

#define MAX 10

typedef struct node *link;
struct node { int v; link next; } ;
struct dag { int V; int E; link *adj; ST tab; link z; } ;

link NEW(int v, link next) { link x = malloc(sizeof *x);
  x->v = v; x->next = next;
  return x;
}

Dag DAGinit(int V) {
  int v;
  Dag D = malloc(sizeof *D);
  if (D == NULL)
    return NULL;

  D->V = V;
  D->E = 0;
  D->z = NEW(-1, NULL);
  D->adj = malloc(D->V*sizeof(link));
  for (v = 0; v < D->V; v++)
    D->adj[v] = D->z;
  D->tab = STinit(V);
  if (D->tab == NULL)
    return NULL;
  return D;
}

void  insertE(Dag D, Edge e) {
  int v = e.v, w = e.w;

  D->adj[v] = NEW(w, D->adj[v]);
  D->E++;
}

void DAGread(Dag D) {
  char name[MAX], src[MAX], dst[MAX];
  FILE *fin;

  printf("Input file name: ");
  scanf("%s", name);
  fin = fopen(name, "r");
  if (fin == NULL)
    exit(-1);

  while(fscanf(fin, "%s %s", src, dst) == 2) {
    int id1 = STsearch(D->tab, src);
    if (id1 == -1)
      id1 = STinsert(D->tab, src);
    int id2 = STsearch(D->tab, dst);
    if (id2 == -1)
      id2 = STinsert(D->tab, dst);
    if (id1 < 0 || id2 < 0)
      continue;
    insertE(D, EDGEcreate(id1, id2));
  }
  return;
}

void DAGwrite(Dag D) {
  int i;
  char name[MAX];
  FILE *fout;
  Edge a[D->E];
  printf("Input file name: ");
  scanf("%s", name);
  fout = fopen(name, "w");
  if (fout == NULL)
    exit(-1);
  DAGedges(D, a);
  for (i = 0; i < D->E; i++)
    fprintf(fout, "%s  %s\n", STretrieve(D->tab, a[i].v),STretrieve(D->tab, a[i].w));
  fclose(fout);
  return;
}

void DAGinsert(Dag D) {
  char src[MAX], dst[MAX];

  printf("Insert first node = ");
  scanf("%s", src);
  printf("Insert second node = ");
  scanf("%s", dst);

  int id1 = STsearch(D->tab, src);
  if (id1 == -1)
    id1 = STinsert(D->tab, src);

  int id2 = STsearch(D->tab, dst);
  if (id2 == -1)
    id2 = STinsert(D->tab, dst);

  if (id1 < 0 || id2 < 0)
      return;

  insertE(D, EDGEcreate(id1, id2));
  return;
}

void  DAGshow(Dag D) {
  int v;
  link t;
  printf("%d vertices, %d edges \n", D->V, D->E);
  for (v=0; v < D->V; v++) {
    printf("%s:\t", STretrieve(D->tab, v));
    for (t=D->adj[v]; t != D->z; t = t->next)
      printf("%s  ", STretrieve(D->tab, t->v));
    printf("\n");
  }
}

void  removeE(Dag D, Edge e) {
  int v = e.v, w = e.w;
  link x;
  if (D->adj[v]->v == w) {
    D->adj[v] = D->adj[v]->next;
    D->E--;
  }
  else
    for (x = D->adj[v]; x != D->z; x = x->next)
      if (x->next->v == w) {
        x->next = x->next->next;
        D->E--;
  }
}

void DAGremove(Dag D) {
  char src[MAX], dst[MAX];

  printf("Insert first node = ");
  scanf("%s", src);
  printf("Insert second node = ");
  scanf("%s", dst);

  int id1 = STsearch(D->tab, src);
  if (id1 == -1)
    id1 = STinsert(D->tab, src);

  int id2 = STsearch(D->tab, dst);
  if (id2 == -1)
    id2 = STinsert(D->tab, dst);

  if (id1 < 0 || id2 < 0) {
    printf("Edge doesn't exist\n");
    return;
  }
  else
    removeE(D, EDGEcreate(id1, id2));
  return;
}

void  DAGedges(Dag D, Edge *a) {
  int v, E = 0;
  link t;
  for (v=0; v < D->V; v++)
    for (t=D->adj[v]; t != D->z; t = t->next)
      if (v < t->v)
        a[E++] = EDGEcreate(v, t->v);
}

void TSdfsR(Dag D, int v, int *ts, int *pre, int *time) {
  link t;
  pre[v] = 0;
  for (t = D->adj[v]; t != D->z; t = t->next)
    if (pre[t->v] == -1)
      TSdfsR(D, t->v, ts, pre, time);
  printf("finita elaborazione di %d\n", v);
  ts[(*time)++] = v;
}

void DAGrts(Dag D) {
  int v, time = 0, *pre, *ts;
  pre = malloc(D->V*sizeof(int));
  ts = malloc(D->V*sizeof(int));

  for (v=0; v < D->V; v++) {
    pre[v] = -1;
    ts[v] = -1;
  }
  for (v=0; v < D->V; v++)
    if (pre[v]== -1)
      TSdfsR(D, v, ts, pre, &time);

  printf("DAG nodes in reverse topological order \n");
  for (v=0; v < D->V; v++)
//     printf("%s ", STretrieve(D->tab, ts[v]));
     printf("%d ", ts[v]);
  printf("\n");

}


