#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Item.h"

struct item {
  char *name;
  int value, has_l, has_r;
};

Item ITEMscan(FILE *fp) {
  char name[MAXC+1];
  Item tmp = (Item) malloc(sizeof(struct item));

  fscanf(fp, " %s %d %d %d", name, &(tmp->value), &(tmp->has_l), &(tmp->has_r));
  tmp->name = strdup(name);
  return tmp;
}

void ITEMshow(Item data) {
  printf("name = %s value = %d\n", data->name, data->value);
}
void ITEMprint(FILE *fp, Item item){
  fprintf(fp, "%s %d %d %d", item->name, item->value, item->has_l, item->has_r);
}

int ITEMcheckvoid(Item data) {
  Key k1, k2="";
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
  if (KEYcompare(k1, k2) == -1) return 1;
  else return 0;
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

int ITEMhasleft(Item item){
  return item->has_l;
}
int ITEMhasright(Item item){
  return item->has_r;
}
void ITEMfree(Item item){
  free(item->name);
  free(item);
}