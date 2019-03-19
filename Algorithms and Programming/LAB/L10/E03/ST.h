#ifndef ST_H_DEFINED
#define ST_H_DEFINED

#include "Item.h"
typedef struct symboltable *ST;

ST  	STinit(int) ;
int 	STinsert(ST, Item) ;
int     STcount(ST st) ;
int     STempty(ST st) ;
Item	STsearch(ST, Key) ;
int     STsearchID(ST st, Key k);
void	STdelete(ST, Key) ;
void	STdisplay(ST) ;
Item    STretrieve(ST, int v);

#endif