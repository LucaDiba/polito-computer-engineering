#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#define MAXC 35

typedef struct item* Item;
typedef char *Key;

Item ITEMscan();
void ITEMshow(Item data);
Item ITEMsetvoid();
void ITEMfree(Item data);
int  ITEMless(Item data1, Item data2);
int  ITEMgreater(Item data1, Item data2);

Key KEYscan();
int KEYcompare(Key k1, Key k2);
Key KEYget(Item data);

int getindex(Key key);

#endif

