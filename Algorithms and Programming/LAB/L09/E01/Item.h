#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#define MAXC 10

typedef struct item* Item;
typedef char *Key;

Item ITEMscan();
void ITEMshow(Item data);
int ITEMcheckvoid(Item data);
Item ITEMsetvoid();
int ITEMless(Item data1, Item data2);
void ITEMfree(Item x);

Key KEYscan();
int KEYcompare(Key k1, Key k2);
Key KEYget(Item data);

void ITEMprint(FILE *, Item);
int ITEMhasleft(Item item);
int ITEMhasright(Item item);
#endif