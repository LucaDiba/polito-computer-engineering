#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

struct item { char *name; int value; };

Item ITEMscan() {
  char name[MAXC];
  int value;

  printf("name = ");
  scanf("%s", name);
  printf("value = ");
  scanf("%d", &value);

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

void ITEMfree(Item data) {
  if (data == NULL)
    return;
  if (data->name != NULL)
    free(data->name);
  free(data);
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

Key KEYscan() {
  char name[MAXC];
  Key k;
  scanf("%s", name);
  k = strdup(name);
  return k;
}

int KEYcompare(Key k1, Key k2) {
  return strcmp(k1, k2);
}

Key KEYget(Item data) {
  return data->name;
}
