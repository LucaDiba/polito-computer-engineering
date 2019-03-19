#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

struct item { char *let; int freq; };

Item ITEMscan() {
  char let[MAXC];
  int freq;

  printf("letter = ");
  scanf("%s", let);
  printf("frequency = ");
  scanf("%d", &freq);

  Item tmp = (Item) malloc(sizeof(struct item));

  if (tmp == NULL)
    return ITEMsetvoid();
  else {
    tmp->let = strdup(let);
    tmp->freq = freq;
  }
  return tmp;
}

Item ITEMnew(Item data1, Item data2) {
  char let[MAXC]="";
  Item tmp = (Item) malloc(sizeof(struct item));
  if (tmp == NULL)
    return ITEMsetvoid();
  else {
    tmp->let = strdup(let);
    tmp->freq = data1->freq + data2->freq;
  }
  return tmp;
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
  char let[MAXC]="";
  Item tmp = (Item) malloc(sizeof(struct item));
  if (tmp != NULL) {
    tmp->let = strdup(let);
    tmp->freq = -1;
  }
  return tmp;
}

int ITEMgreater (Item data1, Item data2) {
  Key k1 = KEYget(data1), k2 = KEYget(data2);
  if (KEYcompare(k1, k2) == 1)
    return 1;
  else
    return 0;
}

int ITEMless (Item data1, Item data2) {
  Key k1 = KEYget(data1), k2 = KEYget(data2);
  if (KEYcompare(k1, k2) == -1)
    return 1;
  else
    return 0;
}

int KEYcompare(Key k1, Key k2) {
  if (k1 < k2)
    return -1;
  else if (k1 == k2)
    return 0;
  else
    return 1;
}

Key KEYget(Item data) {
  return data->freq;
}

Let LETget(Item data) {
  return data->let;
}
