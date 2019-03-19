#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

typedef struct pqueue *PQ;

PQ      PQinit(int);
int     PQempty(PQ);
void    PQinsert(PQ, Item);
Item    PQextractMax(PQ);
Item    PQshowMax(PQ);
void    PQdisplay(PQ);
int     PQsize(PQ);
void    PQchange(PQ pq, int pos, Item item);


#endif
