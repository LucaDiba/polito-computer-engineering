#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symboltable *ST;

ST  	STinit(int) ;
void    STfree(ST) ;
int		STcount(ST) ;
int  	STinsert(ST,Item) ;
int     STsearch(ST,Key) ;
void	STdelete(ST,Key) ;
void	STdisplay(ST) ;

#endif
