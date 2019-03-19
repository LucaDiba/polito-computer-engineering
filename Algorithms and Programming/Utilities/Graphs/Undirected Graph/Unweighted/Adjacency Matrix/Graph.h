#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "ST.h"
#include "Queue.h"


typedef struct graph *Graph;

Graph GRAPHinit(int);
void  GRAPHread(Graph);
void  GRAPHwrite(Graph);
void  GRAPHinsert(Graph);
void  GRAPHremove(Graph);
void  GRAPHedges(Graph, Edge *);
void  GRAPHshow(Graph);
int   GRAPHpath(Graph);
int   GRAPHpathH(Graph);
void  GRAPHbfs(Graph);

#endif
