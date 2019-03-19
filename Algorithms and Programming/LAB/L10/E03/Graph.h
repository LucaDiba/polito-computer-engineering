#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "UF.h"
#include "ST.h"

typedef struct graph *Graph;
typedef struct{
    int intra, inter;
} flussi_t;

Graph GRAPHinit(int);
void  GRAPHread(Graph, FILE*);
void  GRAPHedges(Graph, Edge *);
void  GRAPHshow(Graph);
void  GRAPHmstK(Graph G);
void  GRAPHmstP(Graph G);
int   GRAPHedgesN(Graph G);
void  GRAPHListToMatrix(Graph);
ST    getSTFromGraph(Graph);
void  stampaVertici(ST st);
int   numeroArchiIncidenti(Edge*, Graph, int id_elaboratore_st);
void  stampaVerticiConnessi(int id_elaboratore_st, Graph G);

flussi_t determinaFlussi(Edge*, Graph);

#endif
