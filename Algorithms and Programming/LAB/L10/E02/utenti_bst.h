#ifndef E02_UTENTI_BST_H
#define E02_UTENTI_BST_H

#include "utenti.h"

typedef tab_utenti_t BST;

BST	        BSTinit();
int	    	BSTcount(BST);
int         BSTempty(BST);
utente_t    BSTmin(BST);
utente_t    BSTmax(BST);
void    	BSTinsert_leafI(BST,utente_t);
void    	BSTinsert_leafR(BST,utente_t);
void    	BSTinsert_root(BST,utente_t);
utente_t	BSTsearch(BST,char*);
void	    BSTdelete(BST,char*);
utente_t 	BSTselect(BST,int);
void    	BSTsortinorder(BST);
void    	BSTsortpreorder(BST);
void	    BSTsortpostorder(BST);
utente_t	BSTsucc(BST,char*);
utente_t	BSTpred(BST,char*);


#endif //E02_UTENTI_BST_H
