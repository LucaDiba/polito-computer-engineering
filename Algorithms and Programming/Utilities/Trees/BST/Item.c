#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Item.h"

struct item { char *name; int value; };

Item ITEMscan() {
  char name[MAXC];
  int value;

  //printf("name = ");
  //scanf("%s", name);
  printf("value = ");
  scanf("%d", &value);
  sprintf(name, "%d", value);

  Item tmp = (Item) malloc(sizeof(struct item));
  if (tmp == NULL)
    return ITEMsetvoid();

  else {
    tmp->name = strdup(name);
    tmp->value = value;
  }
  return tmp;
}

void ITEMshow(Item data) {
  printf("name = %s value = %d\n", data->name, data->value);
}

int ITEMcheckvoid(Item data) {
  Key k1, k2=-1;
  k1 = KEYget(data);
  if (KEYcompare(k1,k2)==0)
    return 1;
  else
    return 0;
}

Item ITEMsetvoid() {
  char name[MAXC]="";
  Item tmp = (Item) malloc(sizeof(struct item));
  if (tmp != NULL) {
    tmp->name = strdup(name);
    tmp->value = -1;
  }
  return tmp;
}

int ITEMless (Item data1, Item data2) {
  Key k1 = KEYget(data1), k2 = KEYget(data2);
  if (KEYcompare(k1, k2) < 0)
    return 1;
  else
    return 0;
}

Key KEYscan() {
  Key k;
  scanf("%d", &k);
  return k;
}

int KEYcompare(Key k1, Key k2) {
  return k1 - k2;
}

Key KEYget(Item data) {
  return data->value;
}