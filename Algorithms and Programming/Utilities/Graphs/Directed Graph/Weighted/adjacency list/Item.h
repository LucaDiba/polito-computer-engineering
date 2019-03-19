#ifndef _DATO_INCLUDED
#define _DATO_INCLUDED

#define MAX 10

typedef struct item* Item;
typedef char* Key;

Item ITEMset(Key);
Item ITEMsetvoid();
int  ITEMcheckvoid(Item data);
void ITEMshow(Item data);

Key KEYget(Item data);
int KEYcmp(Key key1, Key key2);


#endif

