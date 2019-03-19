#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#define MAXC 35

typedef struct item* Item;

Item ITEMscan();
void ITEMshow(Item data);
Item ITEMsetvoid();
int ITEMhigh();
int ITEMlow();
int ITEMoverlap(Item data1, Item data2);
int ITEMeq(Item data1, Item data2);
int ITEMless(Item data1, Item data2);
int ITEMless_int(Item data1, int data2);
int ITEMcheckvoid(Item data);
#endif

