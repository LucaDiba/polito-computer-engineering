#include <stdio.h>
#include <stdlib.h>

typedef struct { char name[10]; int size; int value;} Item;

Item ITEMscan();
void ITEMshow(Item x);
