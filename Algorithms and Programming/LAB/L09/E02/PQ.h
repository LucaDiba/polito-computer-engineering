#ifndef _PQ_H
#define _PQ_H

#include "Item.h"

typedef struct pqueue *PQ;
typedef struct{
    Item a, b;
} Item2;

PQ      PQinit(int);
int     PQempty(PQ);
void    PQinsert(PQ, Item);
Item    PQextractMin(PQ);
Item    PQshowMin(PQ);
void    PQStampaRanking(PQ, FILE* fp);
void    PQStampa(PQ, FILE*);
void    PQLeggi(PQ, FILE*);
int     PQsize(PQ);
void    PQchange(PQ, int pos, Item);

void PQadd(PQ);
void PQdeleteItem(PQ, char* nome);
Item2 PQ2less(PQ pq);

#endif //_PQ_H