#ifndef DAG_H
#define DAG_H

#include "Edge.h"
#include "ST.h"

typedef struct dag *Dag;

Dag   DAGinit(int);
void  DAGread(Dag);
void  DAGwrite(Dag);
void  DAGinsert(Dag);
void  DAGremove(Dag);
void  DAGrts(Dag);
void  DAGshow(Dag);
void  DAGedges(Dag, Edge *);
#endif

