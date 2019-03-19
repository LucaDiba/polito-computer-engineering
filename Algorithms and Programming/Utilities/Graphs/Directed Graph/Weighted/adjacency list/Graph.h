#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "ST.h"

typedef struct graph *Graph;

Graph GRAPHinit(int);
void  GRAPHread(Graph);
void  GRAPHinsert(Graph);
void  GRAPHspD(Graph);
void  GRAPHspBF(Graph);
void  GRAPHshow(Graph);

#endif
