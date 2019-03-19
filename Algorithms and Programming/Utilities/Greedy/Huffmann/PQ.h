#ifndef PQ_H_DEFINED
#define PQ_H_DEFINED

typedef struct node* link;

typedef struct pqueue *PQ;

PQ      PQinit(int);
int     PQempty(PQ);
void    PQinsert(PQ, link);
link    PQextractMin(PQ);
int     PQsize(PQ);
Item    NODEextract(link);
link    NEW(Item, link, link);
void    CODEdisplay(link, char*, int);


#endif
