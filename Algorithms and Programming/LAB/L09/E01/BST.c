#include <stdio.h>
#include <stdlib.h>
#include "Item.h"
#include "BST.h"

typedef struct BSTnode* link;
struct BSTnode { Item item; link l; link  r; int N; };

typedef struct{
  int found_1, found_2, found_both, dist;
}DistanzaNodi;

struct binarysearchtree { link head; int N; link z; };
static DistanzaNodi BSTdistanceR(link node, Key k1, Key k2, link z);


link NEW(Item item, link l, link r, int N) {
  link x = malloc(sizeof *x);
  x->item = item; x->l = l; x->r = r; x->N = N;
  return x;
}

BST BSTinit( ) {
  BST bst = malloc(sizeof *bst) ;
  bst->N = 0;
  bst->head = ( bst->z = NEW(ITEMsetvoid(), NULL, NULL, 0));
  return bst;
}

int BSTcountR(link node, link z, int pos, int l1, int l2, int n){
  if(pos > l2 || node == z)
    return n;

  n += BSTcountR(node->l, z, pos+1, l1, l2, n);
  n += BSTcountR(node->r, z, pos+1, l1, l2, n);

  if(pos >= l1)
    if(node->l != z && node->r != z)
      n++;

  return n;
}

int BSTcount(BST tree, int l1, int l2){
  return BSTcountR(tree->head, tree->z, 0, l1, l2, 0);
}

DistanzaNodi DNsetVOID(){
  DistanzaNodi dn;
  dn.found_1 = 0;
  dn.found_2 = 0;
  dn.found_both = 0;
  dn.dist = 0;
  return dn;
}
int pos;
static DistanzaNodi BSTdistanceR(link node, Key k1, Key k2, link z){
  int i;
  DistanzaNodi dn = DNsetVOID(), dn_l, dn_r;

  #ifdef DBG
  printf("\n");
  for(i=0;i<pos;i++)
    printf("\t");
  printf("%s ", KEYget(node->item));
  #endif //DBG
  
  if(node->l != z){
    pos++;
    dn_l = BSTdistanceR(node->l, k1, k2, z);
    pos--;
    if(dn_l.found_1) dn.found_1 = 1;
    if(dn_l.found_2) dn.found_2 = 1;
    if(dn_l.found_1 || dn_l.found_2) dn.dist += dn_l.dist+1;
  }else{
    dn_l = DNsetVOID();
  }

  if(dn_l.found_both)
    return dn_l;
  
  if(node->r != z){
    pos++;
    dn_r = BSTdistanceR(node->r, k1, k2, z);
    pos--;
    if(dn_r.found_1) dn.found_1 = 1;
    if(dn_r.found_2) dn.found_2 = 1;
    if(dn_r.found_1 || dn_r.found_2) dn.dist += dn_r.dist+1;
  }else{
    dn_r = DNsetVOID();
  }

  if(dn_r.found_both)
    return dn_r;

  if((dn_l.found_1 || dn_l.found_2) && (dn_r.found_1 || dn_r.found_2))
    dn.found_both = 1;

  if(!dn.found_1 && KEYcompare(KEYget(node->item), k1)==0)
    dn.found_1 = 1;
  
  if(!dn.found_2 && KEYcompare(KEYget(node->item), k2)==0)
    dn.found_2 = 1;

  if(dn.found_1 && dn.found_2 && !dn.found_both) //sono stati trovati entrambi grazie a questo nodo
    dn.found_both = 1;

  #ifdef DBG
    printf("\n(((%s)))\t", KEYget(node->item));
    printf("\nLEFT dn_l.f_1: %d.\tdn_l.f_2: %d.\tdn_l.f_b: %d\tcnt: %d", dn_l.found_1, dn_l.found_2, dn_l.found_both, dn_l.dist);
    printf("\nRIGH dn_r.f_1: %d.\tdn_r.f_2: %d.\tdn_r.f_b: %d\tcnt: %d", dn_r.found_1, dn_r.found_2, dn_r.found_both, dn_r.dist);
    printf("\nTHIS dn  .f_1: %d.\tdn  .f_2: %d.\tdn  .f_b: %d\tcnt: %d", dn.found_1, dn.found_2, dn.found_both, dn.dist);
    printf("\n");
    for(i=0;i<pos;i++)
      printf("--------");
    printf("RETURN FROM: %s ", KEYget(node->item));
  #endif //DBG
  
  return dn;
}
int BSTdistance(BST tree, Key k1, Key k2){
  DistanzaNodi dn;
  pos=0;
  dn = BSTdistanceR(tree->head, k1, k2, tree->z);
  if(!dn.found_both){
    printf("Non sono state trovate entrambe le chiavi");
    exit(1);
  }
  return dn.dist;
}

link BSTreadPreorderR(FILE *fp, link z){
  Item tmp_item = ITEMscan(fp);
  link p, r, l;
  
  l = ITEMhasleft(tmp_item) ? BSTreadPreorderR(fp, z) : z;
  r = ITEMhasright(tmp_item) ? BSTreadPreorderR(fp, z) : z;

  return NEW(tmp_item, l, r, 0);
}

BST BSTreadPreorder(FILE *fp){
  BST bst = BSTinit();

  bst->head = BSTreadPreorderR(fp, bst->z);

  return bst;
}

void BSTwritePreorderR(FILE *fp, link node, link z, int pos){
  int i;

  if(node == z)
    return;

  for(i=0; i<pos; i++)
    fprintf(fp, "\t");

  ITEMprint(fp, node->item);
  fprintf(fp, "\n");

  BSTwritePreorderR(fp, node->l, z, pos+1);
  BSTwritePreorderR(fp, node->r, z, pos+1);
}
void BSTwritePreorder(FILE *fp, BST bst){
  BSTwritePreorderR(fp, bst->head, bst->z, 0);
}

void BSTswap(link x){
    link tmp;

    tmp = x->l;
    x->l = x->r;
    x->r = tmp;
}
void BSTmirrorR(link x, link z){
    if(x == z)
        return;

    BSTswap(x);
    BSTmirrorR(x->l, z);
    BSTmirrorR(x->r, z);
}
void BSTmirror(BST tree){
    BSTmirrorR(tree->head, tree->z);
}

void BSTfreeR(link x, link z){
    if(x == z)
        return;

    BSTfreeR(x->l, z);
    ITEMfree(x->item);
    free(x->l);

    BSTfreeR(x->r, z);
    ITEMfree(x->item);
    free(x->r);
}
void BSTfree(BST tree){
    BSTfreeR(tree->head, tree->z);
    free(tree);
}