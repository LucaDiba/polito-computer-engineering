#include <malloc.h>
#include <mem.h>
#include <stdio.h>
#include "Item.h"

Item ITEMnew(char*nome, char*id_rete){
    Item item = malloc(sizeof(*item));
    if(item == NULL){
        printf("Errore in allocazione item");
        exit(1);
    }
    strcpy(item->nome, nome);
    strcpy(item->id_rete, id_rete);
    return item;
}

void ITEMshow(Item item){
    printf("Nome: %s - Rete: %s\n", item->nome, item->id_rete);
}

Item ITEMsetvoid(){
    return ITEMnew("", "");
}
int ITEMcheckvoid(Item item){
    if(strcmp(item->nome, "") == 0)
        return 1;
    else
        return 0;
}

Key KEYget(Item item){
    return item->nome;
}

char* getRete(Item item){
    /* Si utilizza strdup per evitare che il client possa ottenere il puntatore
     * alla stringa originale */
    return strdup(item->id_rete);
}

int KEYcompare(Key k1, Key k2){
    return strcmp(k1, k2);
}