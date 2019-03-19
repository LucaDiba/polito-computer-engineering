#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

typedef struct pqueue *PQ;

PQ      PQinit(int);
int     PQempty(PQ);
int     PQsize(PQ);
void    PQinsert(PQ, Item);
Item    PQshowMax(PQ);
Item    PQextractMax(PQ);
void    PQdisplay(PQ, int);
void    PQchange (PQ, Item);


#endif
