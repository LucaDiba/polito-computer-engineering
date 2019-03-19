#include <stdio.h>
#include <stdlib.h>

#define MAXL 11
typedef struct { char name[MAXL]; int size; int value;} Item;

Item ITEMscan();
void ITEMshow(Item x);
