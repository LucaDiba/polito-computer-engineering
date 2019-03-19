#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "ST.h"

typedef struct graph *Graph;

Graph GRAPHinit(int);
void  GRAPHread(Graph);
void  GRAPHwrite(Graph);
void  GRAPHinsert(Graph);
void  GRAPHremove(Graph);
void  GRAPHdfs(Graph G);
int   GRAPHcc(Graph G);
void  GRAPHedges(Graph, Edge *);
void  GRAPHshow(Graph);
void  GRAPHbridge(Graph G);

#endif
