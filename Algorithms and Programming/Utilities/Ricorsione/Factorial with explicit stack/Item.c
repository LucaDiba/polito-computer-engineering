#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

Item ITEMscan()
{
    Item item;
    printf("integer = ");
    scanf("%d", &item.x);
    return item;

}

void ITEMshow(Item item)
{
    printf("%d\n", item.x);
}
