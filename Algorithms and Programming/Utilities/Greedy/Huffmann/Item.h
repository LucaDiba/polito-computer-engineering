#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#define MAXC 3

typedef struct item* Item;
typedef int Key;
typedef char* Let;

Item ITEMscan();
int ITEMcheckvoid(Item data);
Item ITEMsetvoid();
int ITEMgreater(Item data1, Item data2);
int ITEMless(Item data1, Item data2);
Item ITEMnew(Item data1, Item data2);
int KEYcompare(Key k1, Key k2);
Key KEYget(Item data);
Let LETget(Item data);

#endif

