#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symboltable *ST;

ST  	STinit(int) ;
void    STfree(ST) ;
int		STcount(ST) ;
int  	STinsert(ST,Item) ;
int     STlinsearch(ST,Key) ;
int     STbinsearch(ST,Key) ;
void	STdelete(ST,Key) ;
Item    STdisplay_item(ST, int) ;
int     STselect(ST,int)  ;
void	STdisplay(ST) ;

#endif
