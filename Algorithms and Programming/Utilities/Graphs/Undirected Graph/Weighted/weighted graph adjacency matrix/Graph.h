#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "UF.h"
#include "ST.h"

typedef struct graph *Graph;

Graph GRAPHinit(int);
void  GRAPHread(Graph);
void  GRAPHedges(Graph, Edge *);
void  GRAPHshow(Graph);
void  GRAPHmstK(Graph G);
void  GRAPHmstP(Graph G);


#endif
