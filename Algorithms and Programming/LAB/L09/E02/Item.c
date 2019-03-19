#include <stdio.h>
#include <malloc.h>
#include <mem.h>
#include "Item.h"

struct s_partecipante{
    char *nome;
    int punteggio;
};

Item ITEMinit(){
    Item x = malloc(sizeof(*x));
    x->punteggio = 10;
    return x;
}

Item ITEMscan(){
    Item x = ITEMinit();
    char buff[MAX_CHAR_PARTECIPANTE+1];

    printf("Nome partecipante: ");
    scanf("%s", buff);
    x->nome = strdup(buff);

    return x;
}
Item ITEMFileScan(FILE* fp){
    Item x = ITEMinit();
    char buff[MAX_CHAR_PARTECIPANTE+1];

    fscanf(fp, "%*s %s", buff);
    fscanf(fp, "%*s %d", &(x->punteggio));
    x->nome = strdup(buff);

    return x;
}

int ITEMless(Item a, Item b){
    return a->punteggio < b->punteggio;
}
int ITEMgreater(Item a, Item b){
    return a->punteggio > b->punteggio;
}
int ITEMnamecmp(char *cerca, Item item){
    return strcmp(cerca, item->nome);
}
void ITEMshow(Item a, FILE* fp){
    fprintf(fp, "Nome: %s\nPunteggio: %d\n", a->nome, a->punteggio);
}

char* ITEMgetNome(Item item){
    return item->nome;
}
int ITEMgetPunteggio(Item item){
    return item->punteggio;
}
void ITEMcambiaPunteggio(Item item, int nuovo_punteggio){
    item->punteggio = nuovo_punteggio;
}