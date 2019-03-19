#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

typedef struct pqueue *PQ;

PQ      PQinit(int);
int     PQempty(PQ);
void    PQinsert(PQ, int*, int);
int     PQextractMin(PQ pq, int *mindist);
int     PQshowMax(PQ);
void    PQdisplay(PQ);
int     PQsize(PQ);
void    PQchange(PQ, int *min_dist, int);

#endif
