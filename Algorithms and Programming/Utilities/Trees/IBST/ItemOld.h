#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#define EMPTYitem { -1, -1 }
#define overlap(A, B) ((low(A) <= high(B)) && (low(B) <= high(A)))
#define neq(A, B) (low(A) != low(B) || high(A) != high(B))
#define eq(A, B) (low(A) == low(B) && high(A) == high(B))
#define less(A, B) (A < B)
#define less_int(A, B) (low(A) < h->l->max)
#define key(A) (A.x)
#define low(A) (A.x)
#define high(A) (A.y)

typedef struct { int x; int y; } Item;
typedef int Key;

Item ITEMscan();
void ITEMshow(Item x);

#endif
