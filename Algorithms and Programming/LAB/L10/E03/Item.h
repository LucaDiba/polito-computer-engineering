#ifndef E03_ITEM_H
#define E03_ITEM_H

#define MAX_N 30
#define MAX_R 30

typedef struct item_s {
    char nome[MAX_N+1], id_rete[MAX_R+1];
}* Item;
typedef char* Key;

Item ITEMnew(char*nome, char*id_rete);
Item ITEMsetvoid();
int ITEMcheckvoid(Item);
void ITEMshow(Item);

Key KEYget(Item);
int KEYcompare(Key, Key);
char* getRete(Item);
#endif //E03_ITEM_H