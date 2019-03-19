#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symboltable *ST;

ST  	STinit(int) ;
int     STsize(int) ;
int  	STinsert(ST, Item) ;
int     STcount(ST st) ;
int     STempty(ST st) ;
Item 	STgetitem(ST, int) ;
int 	STgetindex(ST, Item) ;
void    STchange(ST, Item);
void	STdisplay(ST) ;

#endif
