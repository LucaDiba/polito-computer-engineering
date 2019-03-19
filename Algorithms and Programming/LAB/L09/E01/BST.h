#ifndef BST_H_DEFINED
#define BST_H_DEFINED

typedef struct  binarysearchtree *BST;

BST	    BSTinit() ;
int		BSTcount(BST, int l1, int l2);
int     BSTempty(BST) ;
Item    BSTmin(BST) ;
Item    BSTmax(BST) ;
void 	BSTinsert_leafI(BST,Item) ;
void 	BSTinsert_leafR(BST,Item) ;
void 	BSTinsert_root(BST,Item) ;
Item	BSTsearch(BST,Key) ;
void	BSTdelete(BST,Key) ;
Item 	BSTselect(BST,int) ;
void	BSTsortinorder(BST) ;
void	BSTsortpreorder(BST) ;
void	BSTsortpostorder(BST) ;
Item	BSTsucc(BST,Key) ;
Item	BSTpred(BST,Key) ;

BST BSTreadPreorder(FILE *fp);
void BSTwritePreorder(FILE *, BST);
int BSTdistance(BST, Key, Key);
void BSTmirror(BST);
void BSTfree(BST);

#endif
