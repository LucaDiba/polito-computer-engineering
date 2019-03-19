#ifndef ST_H_DEFINED
#define ST_H_DEFINED

typedef struct symboltable *ST;

ST  	STinit(int) ;
void    STfree(ST) ;
int		STcount(ST) ;
int  	STinsert(ST, char *) ;
int     STsearch(ST, char *) ;
char*	STretrieve(ST, int) ;

#endif
