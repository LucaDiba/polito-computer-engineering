#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symboltable *ST;

ST  	STinit(int) ;
void    STfree(ST) ;
int		STcount(ST) ;
void  	STinsert(ST,Item) ;
Item    STsearch(ST,Key) ;
void	STdelete(ST,Key) ;
Item    STselect(ST,int)  ;
void	STdisplay(ST) ;

#endif
