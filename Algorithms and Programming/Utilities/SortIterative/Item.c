#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

Item ITEMscan() {
  Item item;
  printf("x = ");
  scanf("%d", &item.x);
  printf("y = ");
  scanf("%d", &item.y);
  return item;
}

void ITEMshow(Item item) {
  printf("a.x= %6d \t a.y= %6d \n", item.x, item.y);
}

Key key(Item item) {
  return item.x;
}


Item ITEMrand() {
  Item item = { maxKey*rand()/RAND_MAX, maxKey*rand()/RAND_MAX};
  return item;
}
