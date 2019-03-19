#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

Item ITEMscan()
{
    Item item;
    printf("Element: \n");
    printf("name = ");
    scanf("%s", item.name);
    printf("size = ");
    scanf("%d", &item.size);
    printf("value = ");
    scanf("%d", &item.value);
    return item;
}

void ITEMshow(Item item)
{
    printf("%s ", item.name);
}

