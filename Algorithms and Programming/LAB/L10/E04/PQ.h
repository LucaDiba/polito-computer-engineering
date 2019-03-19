#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

typedef struct coordinate_s{
    int r, c;
} Item;
typedef struct pqueue *PQ;
struct pqueue {
    Item *A;
    int heapsize;
};

PQ      PQinit(int);
int     PQempty(PQ);
void    PQinsert(PQ pq, int **mindist, Item k);
Item    PQextractMin(PQ, int **);
Item    PQshowMax(PQ);
void    PQdisplay(PQ pq);
int     PQsize(PQ);
void    PQchange(PQ pq, int **mindist, Item k);


#endif
