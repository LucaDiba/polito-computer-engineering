#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

Item ITEMscan()
{
    Item item;
    printf("lower bound = ");
    scanf("%d", &item.x);
    printf("upper bound = ");
    scanf("%d", &item.y);
    return item;

}

void ITEMshow(Item item)
{
    printf("[%d, %d] \n", item.x, item.y);
}
