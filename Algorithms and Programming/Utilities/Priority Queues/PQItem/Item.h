#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#define MAXC 10

typedef struct item* Item;
typedef int Key;

Item ITEMscan();
Item ITEMrand();
Item ITEMsetvoid();
void ITEMshow(Item data);
int ITEMless(Item data1, Item data2);
int ITEMgreater(Item data1, Item data2);

int KEYcompare(Key k1, Key k2);
Key KEYget(Item data);

#endif

