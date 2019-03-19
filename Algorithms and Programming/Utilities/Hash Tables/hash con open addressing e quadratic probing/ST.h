#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symboltable *ST;

ST   	STinit(int) ;
int 	STcount(ST) ;
int     STempty(ST);
void 	STinsert(ST, Item) ;
Item	STsearch(ST, Key) ;
void	STdelete(ST, Key) ;
void	STlist(ST) ;


#endif
