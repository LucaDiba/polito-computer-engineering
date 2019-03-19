#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Item.h"

struct item { int low; int high; };

Item ITEMscan() {
  int value;
  Item data = (Item) malloc(sizeof(struct item));
  if (data == NULL)
    return ITEMsetvoid();
  else {
    printf("lower bound = ");
    scanf("%d", &value);
    data->low = value;
    printf("upper bound = ");
    scanf("%d", &value);
    data->high = value;
  }
  return data;
}

void ITEMshow(Item data) {
  printf("[%d, %d] ", data->low, data->high);
}

Item ITEMsetvoid() {
  Item tmp = (Item) malloc(sizeof(struct item));
  if (tmp != NULL) {
    tmp->low = -1;
    tmp->high = -1;
  }
  return tmp;
}

int ITEMhigh(Item data) {
  return data->high;
}

int ITEMlow(Item data) {
  return data->low;
}

int ITEMoverlap(Item data1, Item data2) {
  if ((data1->low <= data2->high) && (data2->low <= data1->high))
    return 1;
  else
    return 0;
}

int ITEMeq(Item data1, Item data2) {
  if ((data1->low == data2->low) && (data1->high == data2->high))
    return 1;
  else
    return 0;
}

int ITEMless(Item data1, Item data2) {
  if ((data1->low < data2->low))
    return 1;
  else
    return 0;
}

int ITEMless_int(Item data1, int data2) {
  if ((data1->low < data2))
    return 1;
  else
    return 0;
}

int ITEMcheckvoid(Item data) {
  if ((data->low == -1) && (data->high == -1))
    return 1;
  else
    return 0;
}
